/*
 *Li-Chao Tree given an known array for minimization functions.
 * */
#include <bits/stdc++.h>
using namespace std;
struct stFunction{
    long long a, b; //y=ax+b --> 
    long long operator()(long long x){
	return a*x+b;
    }
};
class LiChaoTree{
   vector<stFunction> tree;
   vector<long long> data;
   int n;
   public:
      LiChaoTree(vector<long long> &_data){
	data=_data;
	n=data.size();
	sort(data.begin(), data.end());
	tree.assign(4*n, {0, LONG_MAX});
      }
      void insert(stFunction f){
	   insert(1, 0, n-1, f);
      }
      void insert(int node, int L, int R, stFunction &nFun){
	   int M=(L+R)/2;
	   bool left = (nFun(data[L]) < tree[node](data[L]));
	   bool mid = (nFun(data[M]) < tree[node](data[M]));
	   if(mid) swap(tree[node], nFun);
	   if(L==R) return;
	   if(left != mid)
	     insert(node*2, L, M, nFun);
	   else
	     insert(node*2+1, M+1, R, nFun);
      }
      long long query(long long value){
	 return query(1, 0, n-1, value);
      }
      long long query(int node, int L, int R, long long value){
	  if(L==R){
	     return tree[node](data[L]);
	  }
	  int M=(L+R)/2;
	  if(value<=data[M]){
	     return min(query(node*2, L, M, value), tree[node](value));
	  }else{
	     return min(query(node*2+1, M+1, R, value), tree[node](value));
	  }
      }
};
int main(){
 vector<int> data;
 for(int i = 0; i  < 1000000; i++)data.push_back(i);
 LiChaoTree LCT(data);
 LCT.insert({1, 0});
 cout << LCT.query(1)<<endl;
 LCT.insert({-1, 5});
 cout << LCT.query(1)<<endl;
 cout << LCT.query(6)<<endl;
 cout << LCT.query(2)<<endl;
 return 0;
}
