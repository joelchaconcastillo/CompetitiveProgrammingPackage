#include <bits/stdc++.h>
#define MAX_N 5000
using namespace std;
vector<vector<int> > adjL, STable;
vector<int> values, parent, depth, pathEuler, node2pathEuler, logi;
vector<pair<int, int> > questions;
int N, Q;


void dfs(int node, int _depth){
   depth[node]=	_depth;
   pathEuler.push_back(node);
   node2pathEuler[node]=pathEuler.size()-1;
   for(auto nextNode: adjL[node]){
     dfs(nextNode, _depth+1);
     pathEuler.push_back(node);
   }
}
void buildSTable(){
   logi.assign(MAX_N+1, 0);
   logi[1]=0;
   int sE = pathEuler.size();
   for(int i = 2; i<=sE; i++) logi[i] = logi[i/2]+1;
   STable.assign(logi[sE]+1, vector<int> (sE, 0));
   for(int i = 0; i < sE; i++) STable[0][i] = pathEuler[i];
   for(int j = 1; (1<<j) <= sE; j++){
     for(int i = 0; i + (1<<j)-1 < sE; i++){
	int idx1 = STable[j-1][i];
	int idx2 = STable[j-1][i+(1<<(j-1))];
        int op1 = depth[idx1];
	int op2 = depth[idx2];
        STable[j][i] = (op1 < op2 )? idx1:idx2;
     }
   }
}
void buildLCA(){
   dfs(0,0);
   buildSTable();
}
int RMQ(int a, int b){
  int k = logi[b-a+1]; 
  int x = STable[k][a];
  int y = STable[k][b-(1<<k)+1];
  return  ( depth[x] <= depth[y] )?x:y;
}
int LCA(int a, int b){
  int l = min(node2pathEuler[a], node2pathEuler[b]);
  int u = max(node2pathEuler[a], node2pathEuler[b]);
  return RMQ(l, u);
}
int main(){
   cin >> N;
   adjL.assign(N, vector<int>());
   values.assign(N, 0);
   parent.assign(N, 0);
   depth.assign(N, 0);
   node2pathEuler.assign(N, 0);
   for(auto &i:values) cin>>i;
   for(int i = 1; i < N ; i++){
       cin>>parent[i];
       adjL[parent[i]].push_back(i);
   }  
   buildLCA();
   cin>>Q;
   questions.assign(Q, pair<int, int>());
   for(auto &q:questions){
	cin>>q.first>>q.second;
	cout << LCA(q.first, q.second)<<endl;
   }
   return 0;
}
