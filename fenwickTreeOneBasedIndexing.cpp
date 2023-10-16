#include <bits/stdc++.h>
using namespace std;
struct FenwickTree{
   vector<int> bit;
   int n;
   FenwickTree(int _n){
     this->n=_n;
     bit.assign(n+1, 0);
   }
   FenwickTree(vector<int> &a):FenwickTree(a.size()){
        for(size_t i=0; i < a.size(); i++) add(i, a[i]);
   }
   int sum(int idx){
       int ret=0;
       idx++;
       for(; idx>0; idx -= idx&(-idx)) ret+=bit[idx];
       return ret;
   }
   int sum(int l, int r){
	return sum(r)-sum(l-1);
   }
   void add(int idx, int delta){
	idx++;
        for(; idx<=n; idx += idx&-idx) bit[idx]+=delta; 
   }
   void rangeAdd(int l, int r, int val){
       add(l, val);
       add(r+1, -val); 
   }
};
int main(){
   vector<int> data={1,4,3,5,6,7,2,34,5};
   FenwickTree ft(data);
   cout << ft.sum(3,5)<<endl;
   cout << ft.sum(4,8)<<endl;
   ft.add(4, -100);
   cout << ft.sum(4,8)<<endl;

   return 0;
}
