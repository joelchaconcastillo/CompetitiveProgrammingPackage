#include <bits/stdc++.h>
using namespace std;
/*  This algorithm is only for DAG's
 *  Kahn's algorithm
 *  time  : O(V + E)
 *  space : O(V+E)
 * */
vector<int> kahn(vector<vector<int> > &adj){
  int V=adj.size();
  vector<int> indeg(V, 0);
  for(int i = 0; i < V; i++){
    for(auto to:adj[i]){
	indeg[to]++;
    }
  }
  queue<int> q;
  for(int i = 0; i < V; i++){
      if(indeg[i]==0)q.push(i);
  }
  vector<int> topologicalsort;
  while(!q.empty()){
     auto from=q.front(); q.pop();
     topologicalsort.push_back(from);
     for(auto to:adj[from]){
	indeg[to]--;
	if(indeg[to]==0) q.push(to);
     }
  }
  if(topologicalsort.size()!=V)return {}; //there is a cycle
  return topologicalsort;
}
/*
 * dfs implementation for topological sort, this does not detect cycles
 * */
#define VISITED 1
#define UNVISITED 0
void dfs(int u, vector<int> &dfs_num, vector<vector<int> > &adjList, vector<int> &ts){
   dfs_num[u]=VISITED;
   for(auto v:adjList[u]){
	  if(dfs_num[v]==UNVISITED)
		dfs(v, dfs_num, adjList, ts);
   }
   ts.push_back(u);
}
vector<int> dfsKahn(vector<vector<int>> &adjList){
   int V=adjList.size();
   vector<int> topologicalsort;
   vector<int> dfs_num(V, UNVISITED);
   for(int i = 0; i < V; i++){
	if(dfs_num[i]==UNVISITED)
		dfs(i, dfs_num, adjList, topologicalsort);
   }
   reverse(topologicalsort.begin(), topologicalsort.end());
   return topologicalsort;
}
int main(){

   return 0;
}
