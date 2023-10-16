#include <bits/stdc++.h>
#define MAX_N 100
using namespace std;
int combs[MAX_N][MAX_N];
int comb1(int N, int k){
   if(N==k || k==0)return 1;
   if(combs[N][k]>0) return combs[N][k];
   combs[N][k] = comb1(N-1, k-1) + comb1(N-1, k);
   return combs[N][k];
}
int comb2(int N, int k){
  int M[MAX_N][MAX_N];
  for(int i = 1; i <=N; i++){
	M[i][0]=M[i][i]=1;
	for(int j = 1; j < i; j++)
		M[i][j]= M[i-1][j-1] + M[i-1][j];
  }
  return M[N][k];
}
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout << comb1(10, 3)<<" " << comb2(10,3)<<endl;
}
