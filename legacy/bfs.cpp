#include <bits/stdc++.h>
using namespace std;
int V;
vector<vector<int> > AL;
/*
 * time: O(V+E)
 * space: O(V)
 * */
bool bfs(int source, int dest){
    queue<int> q;
    vector<int> visited(V, false);
    q.push(source);
    while(!q.empty()){
       int node=q.front();
       visited[node]=true;
       if(node==source)return true;
       q.pop();
       for(auto i:AL[node]){
         if(visited[i])continue; 
	 q.push(i);
       }
    }
    return false;
}
int main(){

   return 0;
}
