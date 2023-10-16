#include <bits/stdc++.h>
#define NA 10000000
using namespace std;
typedef vector<int> vi;
class SegmentTree{
  int n;
  int left(int p){return p<<1;}
  int right(int p){return (p<<1)+1;}
  public:
  vi data, tree, lazy;
   SegmentTree(int n){
      this->n = n;
      data.assign(n,0);
      tree.assign(4*n,NA); 
      lazy.assign(4*n,NA); 
   }
   int conquer(int leftVal, int rightVal){
      if(leftVal == NA)return rightVal;
      else if(rightVal== NA)return leftVal;  
      return leftVal+rightVal;
   }
   void propagate(int node, int L, int R){
      if(lazy[node]!=NA){
  	  tree[node] = lazy[node]*(R-L+1);
	  if(L!=R){
	     lazy[left(node)]=lazy[right(node)]=lazy[node];
	  }
	  else tree[L]=lazy[node];
	  lazy[node]=NA;
      }
   }
void updateRange(int node, int L, int R, int i, int j, int val){
      propagate(node, L, R);
      if( R<i || L>j)return;
      if(i<=L && j>=R){
	lazy[node]=val;
	propagate(node, L, R);
	return;
      }else{
      int M = (L+R)/2;
      updateRange(left(node), L, M, i, j, val);
      updateRange(right(node), M+1, R, i, j, val);
      tree[node] = conquer(tree[left(node)], tree[right(node)]);
      }
   }
void build(int node, int L, int R){
      if(L==R){ tree[node]=data[L]; return;}
      int M=(L+R)/2;
      build(left(node), L, M);
      build(right(node), M+1, R);
      tree[node] = conquer(tree[left(node)], tree[right(node)]);
   }
int query(int node, int L, int R, int i, int j){
      propagate(node, L, R);
      if(j < L || i >R ) return NA; 
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
   srand(0);
   SegmentTree st(10);
   for(auto &i:st.data){
      i=rand()%20;
      cout << i <<" ";
   }
   st.build();
   cout<<endl;
   cout << st.query(7, 9)<<endl;
   st.update(8, -199);
   cout << st.query(7, 9)<<endl;
   st.updateRange(1,7, 10000);
   cout << st.query(0, 5)<<endl;
   for(int i = 0; i < 10; i++)cout <<st.query(i,i)<<" ";
   cout<<endl;
   st.updateRange(0,8, 10000);
   cout << st.query(0, 5)<<endl;
   cout << st.query(9, 9)<<endl;
   return 0;
}
