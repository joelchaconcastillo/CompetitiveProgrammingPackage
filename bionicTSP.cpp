#include <bits/stdc++.h>
#define MAX_N 100
using namespace std;
double d[MAX_N][MAX_N];
int memo3d[MAX_N][MAX_N][MAX_N], n;
/*
 *Complexity of O(n^3)
 * */
double dp1(int v, int p1, int p2){
    if(v==n-1)return d[p1][v]+d[v][p2];
    auto &memo=memo3d[v][p1][p2];
    if(memo > -0.5)return memo;
   double LR=dp1(v+1, v,p2)+d[p1][v];
   double RL=dp1(v+1, p1,v)+d[v][p2];
   return memo = min(LR,RL);
}
/*
 *Complexity of O(n^2)
 * */
vector<vector<double>> d, memo2d;
int n;
double dist(pair<double, double> &p1, pair<double, double> &p2){
   return sqrt((p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second));
}
double dp2(int p1, int p2){
    int v = 1+max(p1,p2);
    if(v==n-1)return d[p1][v]+d[v][p2];
    auto &memo=memo2d[p1][p2];
    if(memo > -0.5)return memo;
   double LR=dp2(v,p2)+d[p1][v];
   double RL=dp2(p1,v)+d[v][p2];
   return memo = min(LR,RL);
}
int main(){
	//dp1(1,0,0)
	//dp2(0,0)
    return 0;
}
