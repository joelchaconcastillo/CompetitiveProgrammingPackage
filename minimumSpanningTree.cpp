#include <bits/stdc++.h>
using namespace std;
class UnionFind{
  private:
   vector<int> p, rank, setSize;
   int numSets;
  public:
   UnionFind(int N = 1e5){
	p.assign(N,0);
	for(int i = 0; i < N; i++)p[i]=i;
	rank.assign(N, 0);
	setSize.assign(N, 1);
	this->numSets=N;
   }
   int findSet(int i){  return (p[i]==i)?i:(p[i]=findSet(p[i]));}
   bool connected(int i, int j){return findSet(i)==findSet(j);}
   int numDisjointSets(){return numSets;}
   int sizeOfSet(int i){ return setSize[findSet(i)]; }

   void unionSet(int i, int j){
	if(connected(i, j))return;
	int x = findSet(i), y = findSet(j);
	if( rank[x] > rank[y]) swap(x,y);
	p[x] = y;
        if(rank[x]==rank[y]) rank[y]++; 
	setSize[y] += setSize[x];
	numSets--;
   }
};
/* 
 *  Kruskal's Algorithm
 *  time: O(E log E)
 *  space: O(E)
 * */
pair<double, set<int> > kruskal(vector<vector<pair<int, double> > > &AL, int V){
    vector<pair<double, pair<int,int> > > edges;
    for(int i = 0; i <V; i++){
	for(auto j:AL[i])
	    edges.push_back(make_pair(j.second,make_pair(i, j.first)));
    }
    sort(edges.begin(), edges.end());
    set<int> MST;
    double cost=0;
    UnionFind UF(V);
    for(int i = 0; i < edges.size(); i++){
	auto E=edges[i];
	if(UF.connected(E.second.first, E.second.second))continue;
	UF.unionSet(E.second.first, E.second.second);
	cost +=E.first;
	MST.insert(E.second.first);
	MST.insert(E.second.second);
    }
    return make_pair(cost, MST);
}
/*
 * Prim's Algorithm
 * time:
 * space:
 * */
void process(int node, vector<pair<int, double> > &neighbour, vector<bool> &marked, priority_queue<pair<double, int> > &q){
   marked[node]=true;
   for(auto to:neighbour){
      if(marked[to.first])continue;
      q.push(make_pair(-to.second, to.first)); 
   }
}
pair<double, set<int> > primm(vector<vector<pair<int, double> > > &AL, int V){
   vector<bool> marked(V, false);
   double cost=0.0;
   priority_queue<pair<double, int>> q;
   set<int> tree;
   process(0, AL[0], marked, q);
   while(!q.empty()){
      auto node=q.top();
      q.pop();
      if(marked[node.second])continue;
      tree.insert(node.second);
      cost+=-node.first;
      process(node.second, AL[node.second], marked, q);
   }
   return make_pair(cost, tree);
}
pair<double, set<int> > AlternativePrimm(vector<vector<pair<int, double> > > &AL, int V){
   vector<bool> marked(V, false);
   double cost=0.0;
   priority_queue<pair<double, int>> q;
   set<int> tree;
   q.push(make_pair(0,0)); //it can begin from any node..
   while(!q.empty()){
      auto node=q.top();
      q.pop();
      if(marked[node.second])continue;
      marked[node.second]=true;
      tree.insert(node.second);
      cost+=-node.first;
      for(auto i:AL[node.second]){
	if(marked[i.first])continue;
	q.push(make_pair(-i.second, i.first));
      }
   }
   return make_pair(cost, tree);
}
int main(){

   return 0;
}
