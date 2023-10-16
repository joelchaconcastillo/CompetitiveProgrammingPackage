/*
 * MO-TreePath algorithm
 * */
#include <bits/stdc++.h>
#define MAX_N 5100
using namespace std;
vector<vector<int> > adjL, STable;
vector<int> values, depth, pathEuler, node2pathEuler, logi, node2start, node2end, freq, treePath2Node;
//vector<int> marked;
vector<bool> marked;
struct query{
   int id, l, r, lBlock, lca;
   bool operator <(const query& rhs){
	if(lBlock == rhs.lBlock){
	   return (r < rhs.r);
	}
        return (lBlock < rhs.lBlock);
   }
};
vector<query> queries;
int N, Q, currentVis ;
void dfs(int node, int _depth){
   node2start[node]= currentVis++;
   treePath2Node.push_back(node);
   depth[node]=	_depth;
   pathEuler.push_back(node);
   node2pathEuler[node]=pathEuler.size()-1;
   for(auto nextNode: adjL[node]){
     dfs(nextNode, _depth+1);
     pathEuler.push_back(node);
   }
   node2end[node]=currentVis++;
   treePath2Node.push_back(node);
}
void buildSTable(){
   int sE = pathEuler.size();
   logi.assign(sE+1, 0);
   logi[1]=0;
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
void process(int idx, int &_ans){
   if( marked[idx] && (--freq[values[idx]]==2)) _ans--;
   else if( (!marked[idx]) && (freq[values[idx]]++ == 2)) _ans++;
   marked[idx] = !marked[idx];
}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
   cin >> N;
   adjL.assign(N, vector<int>());
   values.assign(N, 0);
   depth.assign(N, 0);
   node2pathEuler.assign(N, 0);
   node2start.assign(N, 0);
   node2end.assign(N,0);
   freq.assign(MAX_N, 0);
   marked.assign(N, 0);
   currentVis=0;
   for(auto &i:values) cin>>i;
   for(int i = 1; i < N ; i++){
       int pi;
       cin>>pi;
       adjL[pi].push_back(i);
   }  
   buildLCA();
   int SQRT_N = sqrt((int)treePath2Node.size())+1;
   cin>>Q;
   queries.assign(Q, query());
   for(int i = 0; i < Q; i++){
      int from, to;
      cin>> from >> to;
      queries[i].id=i;
      queries[i].lca=LCA(from, to);
      if(node2start[from] > node2start[to])swap(from, to);
      if( from == queries[i].lca) queries[i].l = node2start[from], queries[i].r= node2start[to];
      else queries[i].l = node2end[from], queries[i].r=node2start[to];
      queries[i].lBlock=queries[i].l/SQRT_N;
   }
   sort(queries.begin(), queries.end());
   vector<int> ans(Q, 0);
   int cL = queries[0].l, cR=queries[0].l-1, currentAns=0; 
   for(int i = 0; i < Q; i++){
       while(cL < queries[i].l) process( treePath2Node[cL++], currentAns);
       while(cL > queries[i].l) process( treePath2Node[--cL], currentAns);
       while(cR < queries[i].r) process( treePath2Node[++cR], currentAns);
       while(cR > queries[i].r) process( treePath2Node[cR--], currentAns);


       int from = treePath2Node[cL], to = treePath2Node[cR];
       if( queries[i].lca != from && queries[i].lca != to) 
	  process(queries[i].lca, currentAns);
       ans[queries[i].id]=currentAns;
       if( queries[i].lca != from && queries[i].lca != to) 
	  process(queries[i].lca, currentAns);
   }
   for(int i = 0 ; i < Q; i++) cout << ans[i]<<endl;
   return 0;
}
