#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > AdjList;

/*
 *   time: O(V*E)
 *   space: O(E) for adjacency list
 * */
bool bipartiteCheck(){
   int V = AdjList.size();
   int s=0;
   queue<int> q;
   vector<int> color(V, INT_MAX);
   q.push(s);
   bool isBipartite=true;
   color[s]=0;
   while(!q.empty() & isBipartite){
      auto node = q.front(); q.pop();
      for(auto nxt:AdjList[node]){
         if(color[nxt]==INT_MAX){
	    color[nxt]=1-color[node];
	    q.push(nxt); 
	 }	 
	 else if(color[nxt]==color[node]){
	    return false;
	 }
      }
   }
   return bipartiteCheck;
}
int main(){
     
   return 0;
}
