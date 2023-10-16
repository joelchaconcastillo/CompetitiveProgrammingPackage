#include <bits/stdc++.h>
using namespace std;
vector<bool> visited;
vector<vector<int> > AL; //Adjacency List..
/*
 * for cyclic graphs
 * */
void dfs1(int node){
   visited[node]=true;
   for(auto next:AL[node]){
      if(visited[next])continue;
      dfs1(next);
   }
}
/*
 * for undirected and acyclic graphs
 * */
void dfs2(int node, int prev){
   for(auto next:AL[node]){
    if(next==prev)continue;
    dfs2(next, node);
   } 
}
/*
 * for directed acyclic graphs DAG's
 * */
void dfsDAG(int node){
   for(auto next:AL[node])
	   dfsDAG(next);
}
int main(){
  int n;
  visited.assign(n, false);
  /*
   * read input adjacency list
   * */
  //call
  dfs1(0);
  dfs2(0, -1);
  dfsDAG(0);
  return 0;
}
