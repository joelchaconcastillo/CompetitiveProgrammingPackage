/*
 *This version is taken from:
   https://cp-algorithms.com/data_structures/fenwick.html#finding-sum-in-one-dimensional-array
 * */
#include <bits/stdc++.h>
using namespace std;
struct FenwickTree{
   vector<int> bit;
   int n;
   FenwickTree(int _n){
     this->n=_n;
     bit.assign(n, 0);
   }
   FenwickTree(vector<int>a):FenwickTree(a.size()){
      for(size_t i=0; i<a.size(); i++)  add(i, a[i]);
   }
   int sum(int r){
       int ret=0;
       for(;r>=0; r = (r&(r+1)) - 1) ret +=bit[r];
       return ret;
   }
   inline int sum(int l, int r){ return sum(r)-sum(l-1);}
   void add(int idx, int delta){
       for(; idx<n; idx |= (idx+1)) bit[idx] +=delta;
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
