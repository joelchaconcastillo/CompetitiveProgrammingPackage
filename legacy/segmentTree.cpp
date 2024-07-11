#include <bits/stdc++.h>
#define NA 10000000
using namespace std;
typedef vector<int> vi;
class SegmentTree{
  int n;
  int left(int p){return p<<1;}
  int right(int p){return (p<<1)+1;}
  public:
  vi data, tree;
   SegmentTree(int n){
      this->n = n;
      data.assign(n,0);
      tree.assign(4*n,NA); 
   }
   int conquer(int idxL, int idxR){
      if(idxL == NA)return idxR;
      else if(idxR == NA)return idxL;  
      return idxL+idxR;
//      else if(idxL < idxR)return idxL; //min  
//      //else if(data[idxL] < data[idxR])return idxL; //min  by index
//      else return idxR;
   }
   void update(int node, int L, int R, int idx, int val){
	if( idx < L || idx > R)return;
	if(L==idx && R==idx){
	   data[idx]=val;
	   tree[node]=val; //by value...
	   return;
	}
	int M = (L+R)/2;
	update(left(node), L, M, idx, val);
	update(right(node), M+1, R, idx, val);
	tree[node] = conquer(tree[left(node)], tree[right(node)]);
   }
void updateRange(int node, int L, int R, int i, int j, int val){
      if( R<i || L>j)return;
      if(L==R){
	  data[L]=val;
	  tree[node]=val;//by value
	  return;
      }
      int M = (L+R)/2;
      updateRange(left(node), L, M, i, j, val);
      updateRange(right(node), M+1, R, i, j, val);
      tree[node] = conquer(tree[left(node)], tree[right(node)]);
   }
void build(int node, int L, int R){
      if(L==R){
	      tree[node]=data[L]; 
	      return;
      }
      //if(L==R){ tree[node]=L; return;} // by index..
      int M=(L+R)/2;
      build(left(node), L, M);
      build(right(node), M+1, R);
      tree[node] = conquer(tree[left(node)], tree[right(node)]);
   }
int query(int node, int L, int R, int i, int j){
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
      update(1, 0, n-1, idx, v);
   }
   void updateRange(int i, int j, int val){
	updateRange(1, 0, n-1, i, j, val);
   }
};
int main(){
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
   st.updateRange(1,7, -10000);
   cout << st.query(0, 5)<<endl;
   return 0;
}
