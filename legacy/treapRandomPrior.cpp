#include <bits/stdc++.h>
using namespace std;
struct item{
   int key, prior, cnt;
   item *l, *r;
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
 *Builds a tree in O(N) given an array a[]
 * */
pitem build(int *a, int n){
   if(n==0)return NULL;
   int mid = n/2;
   pitem t=new item(a[mid], rand());
   t->l = build(a, mid);
   t->r = build(a+mid+1, n-mid-1);
   heapify(t);
   upd_cnt(t);
   return t;
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
int main(){
   pitem l = NULL, r=NULL;
   pitem root=new item(3), tmp=new item(4);
   insert(root,tmp);

   //split(t, 5, l,r);
   //if(l) cout <<"left st " <<(l->size)<<endl;
   //if(r) cout<<"right st "<<(r->size)<<endl;
   return 0;
}
