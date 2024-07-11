#include <bits/stdc++.h>
#define MAX 10000000
using namespace std;
/*
 *  time: O(V^2 log E)
 *  space: O(E)
 * */
double dijsktra(vector<vector<pair<int, double> > > &AL, int s, int d){
    int V= AL.size();
    priority_queue<pair<double, int> > q;
    vector<double> minDist(V, MAX);
    minDist[s]=0;
    q.push({0, s});
    while(!q.empty()){
       auto node=q.top();
       q.pop();
       if(-node.first > minDist[node.second])continue;
       for(auto nxt:AL[node.second]){
	 if(minDist[node.second]+nxt.second < minDist[nxt.first]){
	    minDist[nxt.first]=minDist[node.second]+nxt.second;
	    q.push({-minDist[nxt.first], nxt.first});
	 }
       }
    }
    return minDist[d];
}
/*
 * Bellmandford's algorithm
 * time:  O(V*V*V) in adjacency matrix and O(V*E) in adjacency list
 * space:  O(V*V) in adjacency matrix and O(E) in adjacency list
 * */
double bellmanFord(vector<vector<pair<int, double> > > &AL, int s, int d){
   int V=AL.size();
   vector<double> minDist(V, MAX);
   minDist[s]=0;
   for(int i = 0; i < V-1; i++){
      for(int u = 0; u < V; u++){
         for(int j = 0; j <(int)AL[u].size(); j++){
	   auto v = AL[u][j];
	   minDist[v.first] = min(minDist[v.first], minDist[u]+v.second);
	 }
      }
   }
   return minDist[d];
}
bool bellmanFordNegativeCycle(vector<vector<pair<int, double> > > &AL, int s, int d){
   int V = AL.size();
   vector<double> minDist(V, MAX);
   minDist[s]=0;
   bool hasNegativeCucle=false;
   for(int i = 0; i < V-1;i++){
      for(int u=0; u < V; u++){
	for(int j=0; j < (int)AL[i].size() ; j++){
             auto v=AL[i][j];
	     minDist[v.first]=min(minDist[v.first], minDist[u]+v.second);
	}	
      }
   }
   for(int u = 0; u < V-1; u++){
     for(int j = 0; j < (int)AL[u].size(); j++){	     
       auto v=AL[u][j];
       if(minDist[v.first] > minDist[u]+v.second)
	       hasNegativeCucle=true;
     }
   }
   return hasNegativeCucle;
}
/*
 * Alternative Bellmanford's algorithm
 * this version is useful in cases where the path is required and under constraings of type 'at most'
 * time: O(V*E)
 * space: O(V*V)
 * */
double bellmanFordDP(vector<vector<pair<int, double> > > &AL, int s, int d){
  int V=AL.size();
  vector<double> minDist(V, MAX);
  minDist[s]=0;
  for(int i = 1; i<V;i++){
    auto tmp=minDist;
    for(int j = 0; j  < V; j++){//dest...
      for(auto k:AL[j]){
	  minDist[k.first] =  min(minDist[k.first], tmp[j]+k.second);
      } 
    }
  }
  return minDist[d];
}
/*
 * Bellmanford optimized
 *  time: O(V*E)
 *  space: O(V)
 *  In average it has the same complexities, however in average it has better complexities
 * SPFA: Shortest Path Fastest Algorithm
 * */
double bellmanFordOptimized(vector<vector<pair<int, double> > > &AL, int s, int d){
    int V=AL.size();
    vector<double> minDist(V, MAX);
    queue<int> q;
    vector<bool> visited(V, false);
    visited[s]=true;
    q.push(s);
    minDist[s]=0;
    while(!q.empty()){
      auto node=q.front();
      visited[node]=false;
      q.pop();
      for(auto i:AL[node]){
	if( minDist[node]+i.second < minDist[i.first] ){
	   minDist[i.first] = minDist[node]+i.second;
           if(!visited[i.first]){
             q.push(i.first);
             visited[i.first]=true;
           }
	}
      }
    }
    return minDist[d];
}
int main(){
   return 0;
}
