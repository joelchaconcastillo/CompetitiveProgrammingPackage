#include <bits/stdc++.h>
#define MAXN 100000
#define NA INT_MAX
using namespace std;
typedef vector<int> vi;
class Node{
  public:
     Node *left=NULL, *right=NULL;
     long long val=0, lazy=0;
     Node(){
	val=0;
	lazy=0;
     }
};
class SegmentTree{
  Node *root;
  public:
  long long n;
  vi tree, lazy;
   SegmentTree(long long n){
	this->n=n;
	root=new Node;
   }
void insert(Node *node, long long  L, long long R, long long i, long long j){
     if(R<i || L>j)return ;
      if(i<=L && j>=R){
	node->lazy++;
	return;
      }
      long long m=(L+R)/2;
      if(!node->left) node->left=new Node;
      if(!node->right) node->right=new Node;
      insert(node->left, L, m, i, j);
      insert(node->right, m+1, R, i, j);
      long long v1=0, v2=0;
      if(node->left->lazy>0) v1=m-L+1L;
      else v1=node->left->val;
      if(node->right->lazy>0)v2=R-m;
      else v2=node->right->val;
      node->val=v1+v2;
}
void remove(Node *node, long long L, long long R, long long i, long long j){
   if(L>j || i>R)return;
   if(i<=L && j>=R){
      node->lazy--;
      return;
   }
   long long m=(L+R)/2;
   if(!node->left) node->left=new Node;
   if(!node->right) node->right=new Node;
   remove(node->left, L, m, i, j);
   remove(node->right, m+1, R, i, j);
   long long v1=0, v2=0;
   if(node->left->lazy>0) v1=m-L+1;
   else v1=node->left->val;
   if(node->right->lazy>0)v2=R-m;
   else v2=node->right->val;
   node->val=v1+v2;
}
long long query(Node *node, long long L, long long R, long long i, long long j){
      if(j < L || i >R ) return 0; 
      if(!node)return 0;
      if(node->lazy>0) return min(R, j) - max(L, i)+1;
      if(i<=L && j>=R) return node->val;
      long long M = (R+L)/2;
      return query(node->left, L,M, i, j)+query(node->right, M+1,R, i, j);
   }
int query(long long i, long long j){
      return query(root, 0, n-1, i, j-1);
   }
void insert(long long i, long long j){
	insert(root, 0, n-1, i, j-1);
   }
void remove(long long i, long long j){
        remove(root, 0, n-1, i, j-1);
   }
};
int main(){
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     vi data;
     SegmentTree ST(5000000000L);
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
