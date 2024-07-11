#include <bits/stdc++.h>
using namespace std;
vector<int> _rank;
vector<bool> isBipartite;
vector<pair<int,int> > parent;
int n;
void makeSet(int i){
    parent[i]=make_pair(i, 0);
}
pair<int,int> findSet(int v){
   if(v!=parent[v].first){
     int parity = parent[v].second;
     parent[v] = findSet(parent[v].first);
     parent[v].second ^=parity;
   }
   return parent[v];
}
void addEdge(int a, int b){
  auto x = findSet(a), y=findSet(b); 
  //parity of both extremes should be different..
  if(x.second==y.second){ 
     isBipartite[x.first]=false;
  }else{
    if(_rank[x.first]<_rank[y.first])swap(x,y);
    parent[y.first]= make_pair(x.first,x.second^y.second^1);
    isBipartite[x.first] = (isBipartite[x.first] && isBipartite[y.first]);
    if(_rank[x.first]==_rank[y.first])
      _rank[x.first]++;
  }
}
bool sol(){
   n =100;
   isBipartite.assign(n,true);
   parent.assign(n, make_pair(0,0));
   _rank.assign(n, 0);
   for(int i = 0;i < n; i++) makeSet(i);
   vector<pair<int,int>>edgeList;
   for(auto edge:edgeList){
      addEdge(edge.first, edge.second);
      if(!isBipartite[findSet(edge.first).first] || !isBipartite[findSet(edge.second).first])
	 return false;
   }
   return true;
}
int main(){

   return 0;
}
