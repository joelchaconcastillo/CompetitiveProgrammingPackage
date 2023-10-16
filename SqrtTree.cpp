#include <bits/stdc++.h>
using namespace std;
/*
 * Sqrt-tree impelementation
 * 
 * Time complexity:
 *   build:  O(N * loglogN)
 *   update: O(sqrt(N))
 *   query:  O(1)
 * 
 * Memory usage: O(N * loglogN)
 * 
 * Code written by:
 *   Alexander Kernozhitsky (aka gepardo)
 * 
 * Date: 24.04.2018
 */

struct Struct {
	int l, r;
	int cur;
};

typedef Struct SqrtTreeItem;

int ops = 0;

SqrtTreeItem op(const SqrtTreeItem &a, const SqrtTreeItem &b) {
	ops++;
	// if (ops % 10000 == 0) cout << "ops = " << ops << "\n";
	assert(a.l <= a.r && a.r+1 == b.l && b.l <= b.r);
	return {a.l, b.r, a.cur+b.cur};
}

inline int log2Up(int n) {
	int res = 0;
	while ((1 << res) < n) {
		res++;
	}
	return res;
}

class SqrtTree {
private:
	int n, lg, indexSz;
	vector<SqrtTreeItem> v;
	vector<int> clz, layers, onLayer;
	vector< vector<SqrtTreeItem> > pref, suf, between;
	
	inline void buildBlock(int layer, int l, int r) {
		pref[layer][l] = v[l];
		for (int i = l+1; i < r; i++) {
			pref[layer][i] = op(pref[layer][i-1], v[i]);
		}
		suf[layer][r-1] = v[r-1];
		for (int i = r-2; i >= l; i--) {
			suf[layer][i] = op(v[i], suf[layer][i+1]);
		}
	}
	
	inline void buildBetween(int layer, int lBound, int rBound, int betweenOffs) {
		int bSzLog = (layers[layer]+1) >> 1;
		int bCntLog = layers[layer] >> 1;
		int bSz = 1 << bSzLog;
		int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
		for (int i = 0; i < bCnt; i++) {
			SqrtTreeItem ans;
			for (int j = i; j < bCnt; j++) {
				SqrtTreeItem add = suf[layer][lBound + (j << bSzLog)];
				ans = (i == j) ? add : op(ans, add);
				between[layer-1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
			}
		}
	}
	
	inline void buildBetweenZero() {
		int bSzLog = (lg+1) >> 1;
		for (int i = 0; i < indexSz; i++) {
			v[n+i] = suf[0][i << bSzLog];
		}
		build(1, n, n + indexSz, (1 << lg) - n);
	}
	
	inline void updateBetweenZero(int bid) {
		int bSzLog = (lg+1) >> 1;
		v[n+bid] = suf[0][bid << bSzLog];
		update(1, n, n + indexSz, (1 << lg) - n, n+bid);
	}
	
	void build(int layer, int lBound, int rBound, int betweenOffs) {
		if (layer >= (int)layers.size()) {
			return;
		}
		int bSz = 1 << ((layers[layer]+1) >> 1);
		for (int l = lBound; l < rBound; l += bSz) {
			int r = min(l + bSz, rBound);
			buildBlock(layer, l, r);
			build(layer+1, l, r, betweenOffs);
		}
		if (layer == 0) {
			buildBetweenZero();
		} else {
			buildBetween(layer, lBound, rBound, betweenOffs);
		}
	}
	
	void update(int layer, int lBound, int rBound, int betweenOffs, int x) {
		if (layer >= (int)layers.size()) {
			return;
		}
		int bSzLog = (layers[layer]+1) >> 1;
		int bSz = 1 << bSzLog;
		int blockIdx = (x - lBound) >> bSzLog;
		int l = lBound + (blockIdx << bSzLog);
		int r = min(l + bSz, rBound);
		buildBlock(layer, l, r);
		if (layer == 0) {
			updateBetweenZero(blockIdx);
		} else {
			buildBetween(layer, lBound, rBound, betweenOffs);
		}
		update(layer+1, l, r, betweenOffs, x);
	}
	
	inline SqrtTreeItem query(int l, int r, int betweenOffs, int base) {
		if (l == r) {
			return v[l];
		}
		if (l + 1 == r) {
			return op(v[l], v[r]);
		}
		int layer = onLayer[clz[(l - base) ^ (r - base)]];
		int bSzLog = (layers[layer]+1) >> 1;
		int bCntLog = layers[layer] >> 1;
		int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
		int lBlock = ((l - lBound) >> bSzLog) + 1;
		int rBlock = ((r - lBound) >> bSzLog) - 1;
		SqrtTreeItem ans = suf[layer][l];
		if (lBlock <= rBlock) {
			SqrtTreeItem add = (layer == 0) ? (
				query(n + lBlock, n + rBlock, (1 << lg) - n, n)
			) : (
				between[layer-1][betweenOffs + lBound + (lBlock << bCntLog) + rBlock]
			);
			ans = op(ans, add);
		}
		ans = op(ans, pref[layer][r]);
		return ans;
	}
public:
	inline SqrtTreeItem query(int l, int r) {
		return query(l, r, 0, 0);
	}
	
	inline void update(int x, const SqrtTreeItem &item) {
		v[x] = item;
		update(0, 0, n, 0, x);
	}
	
	SqrtTree(const vector<SqrtTreeItem>& a)
		: n((int)a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onLayer(lg+1) {
		clz[0] = 0;
		for (int i = 1; i < (int)clz.size(); i++) {
			clz[i] = clz[i >> 1] + 1; //this calculates the most left bit on for the i-th element
		}
		/*
		 *i  : 0 1 2 3 4 5 6 7 8
		 *clz: 0 1 2 2 3 3 3 3 4
		 * */
		int tlg = lg;
		while (tlg > 1) {
			onLayer[tlg] = (int)layers.size(); //decreasing 5,4,3,2,1,0
			layers.push_back(tlg); //note that layers stores values decreasingly 5,4,3,2,1,0
			tlg = (tlg+1) >> 1;
		}
		for (int i = lg-1; i >= 0; i--) {
			onLayer[i] = max(onLayer[i], onLayer[i+1]);
		}
		int betweenLayers = max(0, (int)layers.size() - 1);
		int bSzLog = (lg+1) >> 1; //Number of bits of log
		int bSz = 1 << bSzLog; //Number of bits considered 2^bSzlog.
		indexSz = (n + bSz - 1) >> bSzLog; // remaining to fulfill a power of two..
		v.resize(n + indexSz);
		pref.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
		suf.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
		between.assign(betweenLayers, vector<SqrtTreeItem>((1 << lg) + bSz));
		build(0, 0, n, 0);
	}
};




int main() {
	mt19937 rnd(chrono::system_clock().now().time_since_epoch().count());
	cout << "Hello, " << rnd() << "!" << endl;
	//int n, m, k; cin >> n >> m >> k;
	int m; cin >> m;
	for (int n = 1; n <= 1; n++) {
		cout << "#" << n << endl;
		vector<SqrtTreeItem> v(n);
		for (int i = 0; i < n; i++) {
			v[i] = Struct {i, i, (int)rnd() % 100 + 1};
		}
		SqrtTree sqt(v);
		for (int i = 0; i < m; i++) {
			//cout << "i = " << i << endl;
			for (int i = 0; i < n; i++) {
				int soom = 0;
				for (int j = i; j < n; j++) {
					soom += v[j].cur;
					auto res = sqt.query(i, j);
					if (!(res.l == i && res.r == j && res.cur == soom)) {
						cout << "bad " << i << " - " << j << " : " << soom << " :: " << res.l << " " << res.r << " " << res.cur << endl;
					}
					assert(res.l == i && res.r == j && res.cur == soom);
				}
			}
			int pos = rnd() % n;
			v[pos].cur = (int)rnd() % 100 + 1;
			sqt.update(pos, v[pos]);
		}
	}
	return 0;
}
