#include <bits/stdc++.h>
#define MAXN 100000
#define NA INT_MAX
using namespace std;
typedef vector<int> vi;
class SegmentTree{
  int left(int p){return p<<1;}
  int right(int p){return (p<<1)+1;}
  public:
  int n;
  vi data, tree, lazy;
   SegmentTree(int n){
      this->n = n;
      data.assign(n,0);
      tree.assign(4*(n),NA); 
      lazy.assign(4*(n),NA); 
   }
   int conquer(int idxL, int idxR){
      if(idxL == NA)return idxR;
      else if(idxR == NA)return idxL;  
      return idxL+idxR;
   }
   void propagate(int node, int L, int R){
     //if(lazy[node]==NA || tree[node]==NA)return;
     if(lazy[node]==NA) return; // || tree[node]==NA)return;
     if(lazy[node] != 2){
	tree[node] = lazy[node]*(R-L+1);
	if(L!=R) lazy[left(node)] = lazy[right(node)] = lazy[node];
	 else data[L]=lazy[node];
     }
     else{
	  tree[node]=(R-L+1)-tree[node];
	  if(L!=R){
	     if(lazy[left(node)]==NA) lazy[left(node)]=2;
	     else if(lazy[left(node)] == 2) lazy[left(node)]=NA;
	     else lazy[left(node)]=1-lazy[left(node)];
	     
	     if(lazy[right(node)]==NA) lazy[right(node)]=2;
	     else if(lazy[right(node)] == 2) lazy[right(node)]=NA;
	     else lazy[right(node)]=1-lazy[right(node)];
	  }
	  else data[L] = tree[node];
     }
     lazy[node]=NA;
  }
void build(int node, int L, int R){
      if(L==R){ tree[node]=data[L]; return;}
      int M=(L+R)/2;
      build(left(node), L, M);
      build(right(node), M+1, R);
      tree[node] = conquer(tree[left(node)], tree[right(node)]);
   }
void updateRange(int node, int L, int R, int i, int j, int val){
      propagate(node, L, R);
      if(i>j ||  R<i || L>j)return;
      if(i<=L && j>=R){
	lazy[node] = val;
	propagate(node, L, R);
	return;
      }
      int M = (L+R)/2;
      updateRange(left(node), L, M, i, j, val);
      updateRange(right(node), M+1, R, i, j, val);
      tree[node] = conquer(tree[left(node)], tree[right(node)]);
}
int query(int node, int L, int R, int i, int j){
      propagate(node, L, R);
      if(i>j || j < L || i >R ) return NA; 
      if(L>=i && j>=R) return tree[node];
      int M = (R+L)/2;
      return conquer(query(left(node), L,M, i, j), query(right(node), M+1,R, i, j));
   }
   int query(int i, int j){
      return query(1, 0, n-1, i, j);
   }
   void build(){
     build(1, 0, n-1);
   }
   void update(int idx, int v){
      updateRange(1, 0, n-1, idx, idx, v);
   }
   void updateRange(int i, int j, int val){
	updateRange(1, 0, n-1, i, j, val);
   }
};
int main(){
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   int T;
   cin>>T;
   while(T--){
      vi data;
      int M;
      cin>>M;
      SegmentTree ST(0);
      for(int i = 0; i < M ; i++){
	string st;
	int count;
	cin>>count>>st;
	for(int j=0; j<count;j++)
	   for(auto w:st) ST.data.push_back(w-'0');
      }
      int n=ST.data.size();
      ST.tree.assign(4*n, NA);
      ST.lazy.assign(4*n, NA);
      ST.n=n;
      ST.build();
      int Q, i, j;
      cin>>Q;
      char op;
      while(Q--){
	cin>>op>>i>>j;
	if(op=='F') ST.updateRange(i,j, 1);
	else if(op=='E') ST.updateRange(i,j, 0);
	else if(op=='I') ST.updateRange(i,j, 2);
	else if(op=='S') cout << ST.query(i, j)<<endl;
      }
	     
   }
   return 0;
}
