#include <bits/stdc++.h>
#define MAX_N 2
using namespace std;

struct Matrix{int mat[MAX_N][MAX_N];};
Matrix matMul(Matrix a, Matrix b){
   Matrix ans; 
   for(int i = 0 ; i < MAX_N; i++){
     for(int j = 0; j < MAX_N; j++){
       ans.mat[i][j]=0;
       for(int k = 0; k < MAX_N; k++){
	ans.mat[i][j] += a.mat[i][k]*b.mat[k][j];
       }
     }
   }
   return ans;
}
Matrix matPow(Matrix base, int p){
   Matrix ans;
   for(int i = 0 ; i < MAX_N; i++)
      for(int j = 0 ; j < MAX_N; j++)
	ans.mat[i][j]= (i==j);
   while(p){
      if(p&1) ans = matMul(ans, base);
      base = matMul(base, base);
      p>>=1;
   }
   return ans;
}
int main(){

   return 0;
}
