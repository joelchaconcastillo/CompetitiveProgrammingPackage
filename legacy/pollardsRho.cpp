/*
   Algorithm to find a prime factor up to 1 x 10^19
*/
#include <bits/stdc++.h>
using namespace std;
#define abs_val(a)(((a)>0)?(a):-(a))
typedef long long ll;
ll mulmod(ll a, ll b, ll c){
  ll x=0, y=a%c;
  while(b>0){
     if(b%2==1) x=(x+y)%c;
     y = (y*2)%c;
     b /=2;
  }
  return x%c;
}
ll gcd(ll a, ll b){return !b ? a: gcd(b, a%b);}
ll pollard_rho(ll n){
  int i = 0,  k = 2;
  ll x = 3, y = 3;
  while(1){
     i++;
     x = (mulmod(x, x, n) + n -1)%n;
     ll d = gcd(abs_val(y-x), n);
     if(d != 1 && d != n) return d;
     if(i == k) y=x, k*=2;
  }
}
int main(){
   //ll n = 2063512844981574047LL;
   ll n = 50;
   ll ans = pollard_rho(n);
   if( ans > n/ans) ans = n/ans;
   cout<<ans<<" "<<n/ans<<endl;
   return 0;
}
