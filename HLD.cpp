/*
 *This version solves the dtpsum problem...
 * */
#include <bits/stdc++.h>
using namespace std;
vector<int> parent, heaviest;
vector<vector<int> > adjlist;
vector<long long> hldPath, segmentTree, weight;
vector<int> rootHLD, depth, node2HLD;
int N, Q;
/*
 *Segment tree section
 * */
long long queryST(int node, int start, int end, int l, int r){
	if(end < l  || start > r)
		return 0;
	if(start >= l && end <= r)
		return segmentTree[node];
	int mid = (start + end)/2;
	long long p1 = queryST(2*node, start, mid, l, r);
	long long p2 = queryST(2*node + 1, mid + 1, end, l, r);
	return p1+p2;
}
void updateST(int node, int start, int end, int idx, long long val){
	if(start == end)
	{
		segmentTree[node] = hldPath[start] = val;
		return ;
	}
	int mid = (start + end)/2;
	if(idx <= mid)updateST(2*node, start, mid, idx, val);
	else updateST(2*node + 1, mid + 1, end, idx, val);
	segmentTree[node] =segmentTree[2*node]+segmentTree[2*node+1];
	//t[node] = t[2*node] > t[2*node + 1] ? t[2*node] : t[2*node + 1];
}
void buildST(int node, int start, int end){
	if(start == end)
	{
		segmentTree[node] = hldPath[start];
		return ;
	}
	int mid = (start + end)/2;
	buildST(2*node, start, mid);
	buildST(2*node + 1, mid + 1, end);
	segmentTree[node] = segmentTree[2*node]+segmentTree[2*node+1];
	//t[node] = (t[2*node] > t[2*node + 1]) ? t[2*node] : t[2*node + 1];
}
//set subtree sizes
int dfs(int from, int _depth){
   depth[from]=_depth;
   int totalSizeT= 1;
   int maxSize = -INT_MAX;
   for(auto to:adjlist[from]){
      int _size = dfs(to, _depth+1);
      if(_size> maxSize){
	 maxSize= _size;
	 heaviest[from]=to;
      }
      totalSizeT +=_size;
   }
   return totalSizeT;
}
void buildHLD(){
   int idxHLD = 0;
   for(int i = 0;i < N; i++){
 if(parent[i] == -1 || heaviest[parent[i]] != i){
      int j = i;
      while(j != -1){
	rootHLD[j]=i;
        node2HLD[j]=idxHLD;
       	hldPath[idxHLD]=weight[j];
	j=heaviest[j];
	idxHLD++;
      }
    }
   }
//return;
//   queue<int> q;
//   q.push(0);
//   vector<bool> marked(N, false);
//   while(!q.empty()){
//    int i = q.front();q.pop();
//    //check that node "i" is a start-node of a sub-path
//    if(!marked[i] &&( parent[i] == -1 || heaviest[parent[i]] != i)){
//      int j = i;
//      while(j != -1){
//	marked[j]=true;
//	rootHLD[j]=i;
//        node2HLD[j]=idxHLD;
//       	hldPath[idxHLD]=weight[j];
//	j=heaviest[j];
//	idxHLD++;
//      }
//    }
//    for(int j = 0; j < adjlist[i].size(); j++){//visitar a los nodos del siguiente nivel
//	int to = adjlist[i][j];
//	q.push(to);
//    }
//   }
//
//  for(int i = 0; i <N ; i++)
//	  cout << hldPath[i]<<" ";
//  cout <<endl;
}
void updateHLD(int idx, long long val){
	updateST(1, 0, N-1, node2HLD[idx], val);
}
long long findHLD(int a, int b){
   long long sum=0;
   while(rootHLD[a]!=rootHLD[b]){
     if( depth[rootHLD[a]] < depth[rootHLD[b]]) swap(a, b);
	sum += queryST(1, 0, N-1, node2HLD[rootHLD[a]], node2HLD[a]);
	a = parent[rootHLD[a]];
   } 
   if(depth[a] > depth[b]) swap(a,b); //a must be the left point..
  sum += queryST(1, 0, N-1, node2HLD[a], node2HLD[b]);
  return sum;
}
int main(){
   cin>>N>>Q;
   weight.assign(N,0);
   parent.assign(N, -1);
   adjlist.assign(N, vector<int>());
   segmentTree.assign(4*N, 0);
   rootHLD.assign(N, 0);
   hldPath.assign(N, -1);
   depth.assign(N, 0);
   heaviest.assign(N, -1);
   node2HLD.assign(N, 0);
   for(int i = 0; i < N; i++) cin>>weight[i];
   for(int i = 1; i <N; i++){
	   cin>>parent[i];
	   adjlist[parent[i]].push_back(i);
   }
   dfs(0, 0);
   buildHLD();
   buildST(1, 0, N-1);
   while(Q--){
      char opc;
      int a,b;
      cin>>opc>>a>>b;
      if(opc=='U')
	updateHLD(a, b);
      else
       cout << findHLD(a,b)<<endl;
   }
   return 0;
}
