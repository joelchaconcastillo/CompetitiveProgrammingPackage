#include <bits/stdc++.h>
#define UNVISITED 100000
using namespace std;
vector<int> dfs_num, dfs_low, dfs_p;
vector<bool> articulation_vertex;
vector<pair<int, int> >bridges;
vector<vector<int> > AdjList;
int dfsNumberCounter, dfsroot, rootChildren;
/*
 * find articulation points and bridges in undirected graph
 *  This dfs variant is proposed by John Edward Hopcroft and Robert Endre Tarjan
 * time: O(V+E)
 * sace: O(V+E)
 *
 * */
void articulationPointsAndBrdige(int u){
  dfs_num[u]=dfs_low[u]=dfsNumberCounter++;
  for(auto nxt:AdjList[u]){
    if(dfs_num[nxt]==UNVISITED){
	if(dfsroot==u)rootChildren++;
	dfs_p[nxt]=u;
        articulationPointsAndBrdige(nxt);
	if(dfs_num[u] <= dfs_low[nxt]) articulation_vertex[u]=true;;
	if(dfs_num[u] < dfs_low[nxt]) bridges.push_back(make_pair(u, nxt)),
	dfs_low[u]=min(dfs_low[u], dfs_low[nxt]);
    }else{
	 if(dfs_p[u]!=nxt) dfs_low[u]=min(dfs_low[u], dfs_num[nxt]);
    }
  }
}
int main(){
  int V=10;
  dfsNumberCounter=0; 
  dfs_num.assign(V, UNVISITED);
  dfs_low.assign(V, UNVISITED);
  dfs_p.assign(V, 0);
  articulation_vertex.assign(V, false);
  for(int i = 0; i < V; i++){
     if(dfs_num[i]!=UNVISITED)continue;
     dfsroot=rootChildren=i;
     articulationPointsAndBrdige(0);
     if(rootChildren>1) articulation_vertex[dfsroot]=true;
  }
  return 0;
}
