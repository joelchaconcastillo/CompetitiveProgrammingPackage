#include <bits/stdc++.h>
#define MAX_N 5000
using namespace std;
vector<vector<int> > adjL;
vector<int> values, parent, depth;
vector<pair<int, int> > questions;
////jump pointers
int MAX_JUMP;
vector<vector<int> > jPointers;
int N, Q;


int LCAJPointers(int n1, int n2){
   if(depth[n1]>depth[n2])swap(n1, n2);
   int dif=depth[n2]-depth[n1];
   for(int i  = MAX_JUMP; i>=0; i--){
      if( dif & (1<<i)) n2=jPointers[n2][i];
   }
   if(n1==n2) return n1;
   for(int i = MAX_JUMP; i>=0; i--){
     if(jPointers[n1][i] != jPointers[n2][i]){
	n1=jPointers[n1][i];
	n2=jPointers[n2][i];
     }
   }
   return jPointers[n1][0];
}
void createJumpPoninters(){
	jPointers.assign(N+1, vector<int> (MAX_JUMP+1, N));
	depth.assign(N+1, -1);
	parent.assign(N+1, N);
	queue<int> pending;
	depth[0]=0;
	parent[0]=0;
	pending.push(0);
	while(!pending.empty()){
	  int node=pending.front();
	  pending.pop();
	  jPointers[node][0]=parent[node]; 
	  for(int i = 1; i <MAX_JUMP+1; i++)
	     jPointers[node][i]=jPointers[jPointers[node][i-1]][i-1];
 	  for(auto next:adjL[node]){
	    if(next==parent[node])continue;
	    depth[next]=depth[node]+1;
	    parent[next]=node;
	    pending.push(next);
	 }
       }
}
void buildLCAJumpPointers(){
  MAX_JUMP = ceil(log(N)/log(2)+1.0);
  createJumpPoninters();  
}
int main(){
   cin >> N;
   adjL.assign(N, vector<int>());
   values.assign(N, 0);
   parent.assign(N, 0);
   depth.assign(N, 0);
   for(auto &i:values) cin>>i;
   for(int i = 1; i < N ; i++){
       cin>>parent[i];
       adjL[parent[i]].push_back(i);
   }  
   buildLCAJumpPointers();
   cin>>Q;
   questions.assign(Q, pair<int, int>());
   for(auto &q:questions){
	cin>>q.first>>q.second;
	cout << LCAJPointers(q.first, q.second)<<endl;
   }
   return 0;
}
