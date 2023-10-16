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
      LiChaoTree(int _n){
	n=_n;
	for(int i = 0 ; i < n ; i++)data.push_back(i);
	tree.assign(4*n, {0, -LONG_MAX});
      }
      void insert(stFunction f){
	   insert(1, 0, n-1, f);
      }
      void insert(int node, int L, int R, stFunction &nFun){
	   int M=(L+R)/2;
	   bool left = (nFun(L) > tree[node](L));
	   bool mid = (nFun(M) > tree[node](M));
	   if(mid) swap(tree[node], nFun);
	   if(L==R) return;
	   if(left != mid)
	     insert(node*2, L, M, nFun);
	   else
	     insert(node*2+1, M+1, R, nFun);
      }
      long long query(int idx){
	 return query(1, 0, n-1, idx);
      }
      long long query(int node, int L, int R, int idx){
	  if(L==R){
	     return tree[node](idx);
	  }
	  int M=(L+R)/2;
	  if(idx<=M){
	     return max(query(node*2, L, M, idx), tree[node](idx));
	  }else{
	     return max(query(node*2+1, M+1, R, idx), tree[node](idx));
	  }
      }
};
int main(){
 LiChaoTree LCT(1000000);
 LCT.insert({1, 0});
 cout << LCT.query(1)<<endl;
 LCT.insert({-1, 5});
 cout << LCT.query(1)<<endl;
 cout << LCT.query(6)<<endl;
 cout << LCT.query(2)<<endl;
 return 0;
}
