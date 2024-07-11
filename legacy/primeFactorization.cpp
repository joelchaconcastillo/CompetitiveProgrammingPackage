#include <bits/stdc++.h>
using namespace std;

const int N = 1000003;
map<int, int> powers;
int smallest_divisor[N];
bool mark[N];
long long divisor_count = 1;
void prime(){
   smallest_divisor[1]=1;
   smallest_divisor[2]=2;
   for(int i = 4; i < N; i+=2){
      mark[i]=true;
      smallest_divisor[i]=2;
   }
   for(int i = 3; i < N; i+=2){
      if(mark[i])continue;
      smallest_divisor[i]=i;
      for(long long j = i*1ll*i; j < N; j+=2*i){
             if(mark[j])continue;
             smallest_divisor[j]=i;
             mark[j]=1;
      }
   }
}


void factorize(int x){
   int p = 0, current_divisor=1;
   while(x>1){
           if(smallest_divisor[x]!=current_divisor){
              if(p>0){
                 divisor_count /= powers[current_divisor]+1;
                 powers[current_divisor] +=p;
                 divisor_count *= powers[current_divisor]+1;
              }
              p=1; current_divisor = smallest_divisor[x];
           }else p++;
           x /=smallest_divisor[x];
   }
   if(p>0){
         divisor_count /= powers[current_divisor]+1;
         powers[current_divisor] +=p;
         divisor_count *= powers[current_divisor]+1;

   }
}

int main(){
   return 0;
}
