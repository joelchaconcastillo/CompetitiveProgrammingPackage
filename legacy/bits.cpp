#include <bits/stdc++.h>
int get(int b, int i){ return (b & (1<<i))>>i; }
int setb(int b, int i){ return b | (1<<i);}
int clear(int b, int i){ return b & ~(1<<i);}
int flip(int b, int i){ return b ^ (1<<i);}
#define isON(S,j)(s&(1ll<<j))
#define setBit(S,j)(s|=(1ll<<j))
#define clearBits(S,j)(S&=~(1ll<<<j))
#define toggleBits(S,j)(S^=(1ll<<j))
#define lowBit(S)(S&(-S))
#define setAll(S,n)(S=(1ll<<n)-1ll)
#define modulo(S,n)((S)&(N-1))  //returns S%N where N is a power of 2
#define isPowerOfTwo(S)(!(S&(S-1)))
#define nearestPowerOfTwo(S)((int)pow(2.0, (int)((log((double)S)/log(2.0))+0.2)))
#define turnOffLastBit(S)((S)&(S-1))
#define turnOnLastZero(S)((S)|(S+1))
#define turnOffLastConsecutiveBits(S)((S)&(S+1))
#define turnOnLastConsecutiveZeroes(S)((S)|(S-1))

using namespace std;
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   return 0;
}
