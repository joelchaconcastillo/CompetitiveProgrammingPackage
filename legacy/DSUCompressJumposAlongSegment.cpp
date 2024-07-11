/*
 * It's complexity is O(log(n)) but it can be improved to O(alpha(n)) taking into account union by rank heuristic and an extra array "end[]"
 * */
#include <bits/stdc++.h>
using namespace std;
vector<int>parent, ar, ans;
vector<pair<int,pair<int, int> >>queries;
int n, m;
void init(int _n){
  parent.assign(_n, 0);
}
void makeSet(int i){
   parent[i]=i;
}
//path compression...
int findSets(int v){ return (v!=parent[v])?(parent[v]=findSets(parent[v])):v;} 
void sol(){
   n=10;
   m=4;
   queries.assign(m, pair<int, pair<int,int>>());
   ans.assign(m, 0);
   ar.assign(n,0);
   init(n);
   for(int i = 0 ; i < n ; i++) makeSet(i);
   for(int i = m-1; i>=0; i--){ 
      int l=queries[i].first, r=queries[i].second.first, c=queries[i].second.second;
      for(int v=findSets(l); v<=r; v=findSets(v)){
	ar[v]=c;
	parent[v]=v+1;	
      }
   }
}
int main(){
      return 0;
}
