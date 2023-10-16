/*
 * X,Y:
 *  X--> binary tree
 *  Y-->Max heap
 * */
#include <bits/stdc++.h>
using namespace std;
struct item{
   int key, prior, cnt;
   item *l, *r, *p;
   item(){}
   item(int key) : key(key), prior(rand()), l(NULL), r(NULL){}
   item (int key, int prior):key(key), prior(prior), l(NULL), r(NULL){}
};
typedef item *pitem;
int cnt(pitem t){return t?t->cnt:0;}
void upd_cnt(pitem t){
   if(t) t->cnt=1+cnt(t->l) + cnt(t->r);
}
void heapify(pitem t){
   if(!t)return ;
   pitem max=t;
   if(t->l && t->l->prior > max->prior) max = t->l;
   if(t->r && t->r->prior > max->prior){
      max = t->r;
      if(max != t){
	swap(t->prior, max->prior);
	heapify(max);
      }
   }
}
/*
 * O(log N)
 **/
void split(pitem t, int key, pitem &l, pitem &r){
   if(!t) l=r=NULL;
   else if(t->key <= key) split(t->r, key, t->r ,r), l=t;
   else split(t->l, key,l, t->l), r=t;
   upd_cnt(t);
}
/*
 * O(log N)
 * */
void insert(pitem &t, pitem it){
   if(!t) t=it;
   else if(it->prior >t->prior) split(t, it->key, it->l, it->r), t=it;
   else insert(t->key <=it->key ? t->r:t->l, it);
   upd_cnt(t);
}
/*
 * l->key < r->key
 * O(log N)
 * */
void merge(pitem &t, pitem l, pitem r){
  if(!l || !r) t=l?l:r;
  else if(l->prior > r->prior) merge(l->r, l->r, r), t=l;
  else merge(r->l, l, r->l), t=r;
   upd_cnt(t);
}
void erase(pitem &t, int key){
   if(t->key == key){
	pitem th = t;
	merge(t, t->l, t->r);
	delete th;
   }else erase(key < t->key?t->l:t->r, key);
   upd_cnt(t);
}
/*
 *l->prior > r->prior
  O(M*log(N/M))
 * */
pitem unite(pitem l, pitem r){
   if(!l || !r) return l?l:r;
   if(l->prior < r->prior)swap(l,r);
   pitem lt, rt;
   split(r, l->key, lt, rt);
   l->l = unite(l->l, lt);
   l->r = unite(l->r, rt);
   return l;
}
pitem build(vector<int> &a){
   pitem T=NULL;
   for(auto i:a){
     pitem tt= new item(i);
     insert(T, tt);
   }
   return T;
}
/*
 *Builds a tree in O(N) given an array a[] iff the array is sorted!!
 * */

pitem build(int *a, int n){
   sort(a, a+n);
   if(n==0)return NULL;
   int mid = n/2;
   pitem t=new item(a[mid], rand());
   t->l = build(a, mid);
   t->r = build(a+mid+1, n-mid-1);
   heapify(t);
   upd_cnt(t);
   return t;
}
void connect(auto from, auto to){
   vector<pitem> st;
   for(auto it=from; it!=to;it++){  
      while(!st.empty() && st.back()->prior > (*it)->prior)
	st.pop_back();
      if(!st.empty()){
	if(!(*it)->p || (*it)->p->prior > st.back()->prior)
	   (*it)->p=st.back();
      }
      st.push_back(*it);
   }
}
pitem build(int *x, int *y, int n){
   vector<pitem> nodes(n);
   for(int i = 0 ; i <n; i++)
      nodes[i] = new item(x[i], y[i]);
   connect(nodes.begin(), nodes.end());
   connect(nodes.rbegin(), nodes.rend());
   for(int i = 0 ; i < n ; i++){
      if(nodes[i]->p){ 
	if(nodes[i]->p->key < nodes[i]->key)
	  nodes[i]->p->r = nodes[i];
	else
	  nodes[i]->p->l = nodes[i];
      }
   }
   return nodes[max_element(y, y+n)-y];
}
void print(pitem T){
  if(!T)return;
  print(T->l);
  cout<<T->key<<endl;
  print(T->r);
}
int kth(pitem T, int k){
  if(!T)return -1;
  if(cnt(T->l)+1==k)return T->key;
  if(cnt(T->l)+1<k) return kth(T->r, k-cnt(T->l)-1);
  else return kth(T->l, k); 
}
int query(pitem T, int a, int b, int k){
    pitem T1, T2, T3, T4;
    split(T, b, T1, T2);
    split(T1, a-1, T3, T4);
    int res = kth(T4, k);
    merge(T1, T3, T4);
    merge(T,T1, T2);
    return res;
}
int main(){
   int A[]={1,23,4,5,6,7,9};
   vector<int> B={1,23,4,5,6,7,9};
   auto T = build(A, 7); //plus random heap!
   print(T);
   cout <<"find the 2-kth from values 4 to 9:"<<endl;
   cout<<query(T, 4, 9, 2)<<endl;
   return 0;
}
