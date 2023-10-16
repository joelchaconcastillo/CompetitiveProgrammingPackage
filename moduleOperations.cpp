#include <bits/stdc++.h>
using namespace std;
int mod;
const int N = 3e6+7;
int inv[N+1], lprime[N+1], M, P=0;
int multiply(int a, int b){
   while(b%M==0){
	b /=M;
	P++;
   }
   return (a*(b%M))%M;
}
int divide(int a, int b){
   while(b%M==0){
      b /=M;
      P--;
   }
   return (a*inv[b%M])%M;
}

long long binpow(long long a, long long b, long long mod){
    long long res=1;
    a%=mod;
    while(b){
        if(b&1) res=(res*a)%mod;
        b /=2;
        a = (a*a)%mod;
    }
    return res;
}
long long inverse(long long a, long long mod){
   return binpow(a, mod-2, mod);
}
int main(){
  inv[1]=1;
   for(int i=2; i < N && i < M;i++){
       inv[i]=M-inv[M%i]*(M/i)%M;
   }
   for(int i = 2; i< N; i++){
      if(lprime[i]!=0)continue;
      for(int j = i; j <N; j+=i){
	      if(lprime[j]!=0)continue;
	      lprime[j]=i;
      }
   }

   return 0;
}
