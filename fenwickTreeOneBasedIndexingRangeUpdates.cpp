#include <bits/stdc++.h>
using namespace std;
struct FenwickTree{
   vector<int> B1, B2;
   int n;
   FenwickTree(int _n){
     this->n=_n;
     B1.assign(n+1, 0);
     B2.assign(n+1, 0);
   }
   FenwickTree(vector<int> &a):FenwickTree(a.size()){
        for(size_t i=0; i < a.size(); i++) rangeAdd(i, i, a[i]);
   }
   int sum(vector<int> &bit, int idx){
       int ret=0;
       idx++;
       for(; idx>0; idx -= idx&(-idx)) ret+=bit[idx];
       return ret;
   }
   void add(vector<int> &bit, int idx, int delta){
	idx++;
        for(; idx<=n; idx += idx&-idx) bit[idx]+=delta; 
   }
   void rangeAdd(int l, int r, int delta){
       add(B1, l, delta);
       add(B1, r+1, -delta); 
       add(B2, l, delta*(l-1)); 
       add(B2, r+1, -delta*r); 
   }
   int prefixSum(int idx){
       return sum(B1, idx)*idx - sum(B2, idx);
   }
   int rangeSum(int l, int r){
       return prefixSum(r)-prefixSum(l-1);
   }
};
int main(){
   vector<int> data={1,4,3,5,6,7,2,34,5};
   FenwickTree ft(data);
   cout << ft.rangeSum(3,5)<<endl;
   cout << ft.rangeSum(4,8)<<endl;
   ft.rangeAdd(0,7, -100);
   cout << ft.rangeSum(4,8)<<endl;

   return 0;
}
