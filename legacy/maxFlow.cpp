#include <bits/stdc++.h>
#define MAXV 1000
using namespace std;
int res[MAXV][MAXV], mf, f, s, t, V; // res: residual, mf: max flow, f:current flow, s:source, t:sink, V:number of node
vector<int> p;
/*
 *  Ford Fulkerson's Algorithm
 *  time: O(|f*| * E) where |f*| is the max flow value
 * */
int dfs(int node, int t, int currentf){
   if(node==t)return currentf;
   for(int v = 0; v < V; v++){
       if(res[node][v]==0)continue;
       auto minf = dfs(v, t, min(currentf, res[node][v]));
       if(minf != INT_MAX){
	       res[node][v] -= minf;
	       res[v][node] += minf;
	       return minf;
       }
   }
   return INT_MAX;
}
int FordFulkerson(int s, int t){
   int mf=0;
   int f=0;
   while(f!=INT_MAX){
     f=dfs(s, t, 0);
     if(f==INT_MAX)break;
     mf+=f;
   }
   return mf;
}

/*
 * Edmonds Karp's Algorithm
 * time:  O(V*E*E)
 * */
void augment(int v, int minEdge){
   if(s==v){f=minEdge; return;}
   else if(p[v] != -1){
      augment(p[v], min(minEdge, res[p[v]][v]));
      res[p[v]][v] -=f;
      res[v][p[v]] +=f;
   }
}
int edmondKarp(int s, int t){
   mf=0;
   while(true){
      f=0;
      vector<int> dist(V, INT_MAX);
      dist[s]=0;
      queue<int> q;
      q.push(s);
      p.assign(V, -1);
      while(!p.empty()){
        auto u = q.front();
        q.pop();	
	if(u==t)break;
	for(int v = 0; v < V; v++){
	   if(res[u][v]>0 && dist[v]==INT_MAX){
	       dist[v] = dist[u]+1;
	       q.push(v);
	       p[v]=u;
	   }
	}
      }
      augment(t, INT_MAX);
      if(f==0)break;
      mf+=f;
   }
   return mf;
}
int main(){
   return 0;
}
