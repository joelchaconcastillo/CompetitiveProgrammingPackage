/*
 *  min heap
 *  Merge operations in O(log n) on average.
 *  Worst case: The probability that the operation will require more than c*log(n) steps is less than n^{-\epsilon} where \epsilon and c are positive constant
 * */
#include <bits/stdc++.h>
using namespace std;

struct Tree{
   int value;
   Tree *l = NULL, *r=NULL;
   Tree(int value):value(value){
   }
};
class randomizedMinHeap{
   public:
    Tree* root=NULL;
    randomizedMinHeap(){
    }
    Tree* merge(Tree* t1, Tree *t2){
       if(!t1 || !t2) return t1?t1:t2;
       if(t2->value < t1->value) swap(t1, t2);
       if(rand()&1) swap(t1->l, t1->r);
       t1->l = merge(t1->l, t2);
       return t1;
    }
    void insert(int val){
      auto tmp=new Tree(val); 
      root=merge(root, tmp); 
    }
    void pop(){
       if(!root)return;
       if(root->l || root->r){
	  auto tmp =root;
          root = merge(root->l, root->r);
	  delete tmp;
       }
       else delete root, root=NULL;
    }
    int top(){
	if(!root)return -1;
	return root->value;
    }
};
int main(){
   randomizedMinHeap rMinHeap;
   rMinHeap.insert(10);
   cout<<rMinHeap.top()<<endl;
   rMinHeap.insert(100);
   cout<<rMinHeap.top()<<endl;
   rMinHeap.insert(-10);
   cout<<rMinHeap.top()<<endl;
   rMinHeap.pop();
   rMinHeap.pop();
   rMinHeap.pop();
   rMinHeap.insert(-10);
   cout<<rMinHeap.top()<<endl;

   return 0;
}
