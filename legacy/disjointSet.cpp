#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

class UnionFind{
  private:
   vi p, rank, setSize;
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
int main(){
   UnionFind uf(10);
  uf.unionSet(0,1);
  uf.unionSet(0,2);
  uf.unionSet(0,3);
   cout << uf.connected(1,3)<<endl;
   cout << uf.sizeOfSet(0)<<endl;
   cout << uf.numDisjointSets()<<endl;
   return 0;
}
