#include <bits/stdc++.h>
using namespace std;
int n, len;
int query(vector<int> &a, vector<int> &b, int l, int r){
   int sum=0;
   int c_l=l/len, c_r=r/len;
   if(c_l==c_r){
     for(int i = l; i <=r; i++) sum+=a[i];
   }
   else{
       for(int i = l; i < (c_l+1)*len; i++)sum+=a[i];
       for(int i = c_l+1; i < c_r; i++)sum+=b[i];
       for(int i = c_r*len; i <=r; i++)sum+=a[i];
   }
   return sum;
}
int main(){
   vector<int> a={1,6,7,3,5,6,7, 66,5,4,2,56,7,5,3,2};
   n=a.size(), len=sqrt(n)+1;
   vector<int>b(len,0);
   //pre-process...
   for(int i = 0 ; i < n ; i++) b[i/len]+=a[i];
   cout << query(a, b, 0, 5) << endl;
   cout << query(a, b, n-2, n-1) << endl;
   cout << query(a, b, 0, 0) << endl;
   cout << query(a, b, 5, 7) << endl;
  return 0;
}
