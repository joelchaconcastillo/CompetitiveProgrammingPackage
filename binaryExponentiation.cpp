#include <bits/stdc++.h>
using namespace std;
long long recursiveBinPow(long long a, long long n){
   if( n == 0)return 1;
   long long res=recursiveBinPow(a, n/2);
   if( (n&1)==0 ) return res*res;
   else return res*res*a;
}
long long fastBinPow(long long a, long long n){
   long long res=1;
   while(n){
      if(n&1) res *=a;
      a*=a;
      n>>=1;
   }
   return res;
}
long long fastBinPowMod(long long a, long long n, long long m){
   long long res=1;
   a %=m;
   while(n){
      if(n&1) res = (res*a)%m;
      a = (a*a)%m;
      n>>=1;
   }
   return res;
}
/*
 *  3 = 011
 *       42 
 * */
long long fastProd(long long a, long long b){
   long long res=0;
   while(b){
     if(b&1) res = res+a;
     a =2*a;
     b>>=1;
   }
   return res;
}
int main(){
   cout << recursiveBinPow(2, 10)<<endl;
   cout << fastBinPow(2, 10)<<endl;
   cout << fastBinPowMod(2, 10,10)<<endl;
   cout << fastProd(9, 11)<<endl;
   return 0;
}
