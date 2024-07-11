#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100
struct AugmentedMatrix{
   double mat[MAX_N][MAX_N+1];
};
struct ColumnVector{
  double vec[MAX_N];
};
ColumnVector GaussianElimination(int N, AugmentedMatrix Aug){
   ColumnVector X;
   for(int j =0; j < N-1; j++){
      int l = j; 
      for(int i =j+1; i< N; i++) if( fabs(Aug.mat[l][j])  < fabs(Aug.mat[i][j])) l=i; //max abs row.. numeric stability
      for(int k = j; k <= N; k++)swap(Aug.mat[j][k], Aug.mat[l][k]);
      for(int i=j+1; i < N; i++)
	  for(int k = N; k >=j; k--)
		  Aug.mat[i][k] -= Aug.mat[j][k]*Aug.mat[i][j] / Aug.mat[j][j];
   }
   for(int j = N-1; j>=0; j--){
      double t=0.0;
      for(int k = j+1; k <N; k++) t += Aug.mat[j][k]*X.vec[k];
      X.vec[j] = (Aug.mat[j][N] - t)/Aug.mat[j][j];
   }
   return X;
}
int main(){
  return 0;
}
