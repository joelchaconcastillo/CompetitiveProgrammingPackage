#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> > parent;
vector<int> _rank;
int n;
void makeSet(int v){
   parent[v]=make_pair(v,0);
   _rank[v]=0;
}
/*
 * Path compression..
 * */
pair <int,int> findSet(int v){
  if(v!=parent[v].first){
     int len = parent[v].second;
     parent[v] = findSet(parent[v].first);
     parent[v].second +=len;
  }
  return parent[v];
}
/**
 * union by rank heuristic..
 * */
void unionSets(int a, int b){
  int x=findSet(a).first, y=findSet(b).first;
  if(x!=y){
    if(_rank[x]<_rank[y]) swap(x,y);
    parent[y] = make_pair(x, 1);
    if(_rank[x]==_rank[y]) _rank[x]++;
  }
}
int main(){
   n =100; 
   _rank.assign(n, 0);
   parent.assign(n,make_pair(0,0));
   for(int i = 0; i < n; i++) makeSet(i);
   return 0;
}
