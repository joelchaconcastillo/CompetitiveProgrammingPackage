#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+69, k = 19, bits=30;
vector<int> g[maxn];
int n, a[maxn], up[maxn][k], tin[maxn], tout[maxn], timer, d[maxn];

void dfs(int v, int p, vector<int> b){
   tin[v] = ++timer; //first time to visit node v
   up[v][0] = p; //retrieve parent of v node
   d[v] = d[p]+1; //increase depth
   for(int i = 1; i < k; i++){
      up[v][i] = up[up[v][i-1]][i-1];
   }
   for(auto u:g[v]) //go no neighbours...
      if(u != p) dfs(u, v, b); //avoid parent cycles...
   tout[v]=timer;
}
bool is_anc(int u, int v){//check if node u is ancester of node v
   return tin[u] <= tin[v] && tout[u]>=tout[v];
}
int lca(int u, int v){//retrieve the lowest common ancester between u and v
   if(is_anc(u,v)) return u;
   else if(is_anc(v,u))return v;
   for(int i = k-1; i>=0; i--){
       if(!is_anc(up[u][i], v) && up[u][i]>0) u = up[u][i];
   }
   return up[u][0];
}
int OR(int u, int dis){ //bit jumps...
   int res = a[u];
   for(int j = 0 ; j < bits; j++)
      if(dis & (1<<j)) res |= r[u][j], u=up[u][j];
   return res;
}
int Qry(int u, int v){
   int lc = lca(u,v);
   return OR(u, d[u]-d[lc]) | OR(v, d[v]-d[lc]);
}

int main(){
   return 0;
}
