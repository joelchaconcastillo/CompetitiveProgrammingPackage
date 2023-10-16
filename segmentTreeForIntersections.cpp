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
  vi tree, lazy;
   SegmentTree(int n){
      this->n = n;
      tree.assign(4*(n),0); 
      lazy.assign(4*(n),0); 
   }
void insert(int node, int L, int R, int i, int j){
      if(R<i || L>j)return ;
      if(i<=L && j>=R){
	lazy[node]++;
	return;
      }
      int m=(L+R)/2;
      insert(left(node), L, m, i, j);
      insert(right(node), m+1, R, i, j);
      int v1=0, v2=0;
      if(lazy[left(node)]>0) v1= m-L+1;
      else v1=tree[left(node)];
      if(lazy[right(node)]>0) v2= R-m;
      else v2=tree[right(node)];
      tree[node] = v1+v2;
}
void remove(int node, int L, int R, int i, int j){
   if(L>j || i>R)return;
   if(i<=L && j>=R){
      lazy[node]--;
      return;
   }
   int m=(L+R)/2;
   remove(left(node), L, m, i, j);
   remove(right(node), m+1, R, i, j);
   int v1=0, v2=0;
      if(lazy[left(node)]>0) v1= m-L+1;
      else v1=tree[left(node)];
      if(lazy[right(node)]>0) v2= R-m;
      else v2=tree[right(node)];
      tree[node] = v1+v2;
}
int query(int node, int L, int R, int i, int j){
      if(j < L || i >R ) return 0; 
      if(lazy[node]>0) return min(R, j) - max(L, i)+1;
      if(i<=L && j>=R) return tree[node];
      int M = (R+L)/2;
      int v1=query(left(node), L,M, i, j);
      int v2=query(right(node), M+1,R, i, j);
      return v1+v2;
   }
int query(int i, int j){
      return query(1, 0, n-1, i, j-1);
   }
void insert(int i, int j){
	insert(1, 0, n-1, i, j-1);
   }
void remove(int i, int j){
        remove(1, 0, n-1, i, j-1);
   }
};
int main(){
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     vi data;
     SegmentTree ST(500000);
     int N, i,j;
     cin>>N;
     char op;
     while(N--){
       cin>>op>>i>>j;
       if(op=='I') ST.insert(i,j);
       else if(op=='E') ST.remove(i,j);
       else if(op=='Q') cout << ST.query(i,j)<<endl;
     }
     return 0;
}
