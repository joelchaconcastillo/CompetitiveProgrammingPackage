#include <bits/stdc++.h>
using namespace std;
struct Node{
   int value;
   Node *left, *right;
   Node(int _value){
	value=_value;
	left=right=NULL;
   }
};
//recursive version..
class BST{
   Node *root=NULL;
   public:
   BST(){}
   Node *insert(Node *current, int val){
     if(!current){
       Node *tmp=new Node(val);
       return tmp;
     }
     if(val < current->value){
	current->left=insert(current->left, val);
     }else{
        current->right=insert(current->right, val);
     }
     return current;
   }
   Node *remove(Node *current, int val){
        if(!current)return current;
	if(val<current->value)
	   current->left = remove(current->left, val);
	else if(val>current->value)
	   current->right = remove(current->right, val);
	else{ //there is a fit!!
	    if(!current->right){
	      Node *tmp=current->left;
	      delete current;
	      return tmp;
	    }
	    else if(!current->left){
	      Node *tmp=current->right;
	      delete current;
	      return tmp;
	    }else{ //current has both left and right
	      // Node *tmp=current->right;
	      // while(tmp->left)tmp=tmp->left;
	      //option 1!!
	      // current->value = tmp->value;
	      // current->right = remove(current->right, tmp->value);
	      //option 2!!
 	      Node *tmp=current->right, *parent=current;
	      while(tmp->left)parent = tmp, tmp=tmp->left;
	      if(current != parent)
		parent->left=tmp->right;
	      else
		parent->right=tmp->right;
	      current->value=tmp->value;
	      delete tmp;
	    }
	}
	return current;
   }
   void inorder(Node *current){
	if(!current)return;
	if(current->left) inorder(current->left);
	cout <<current->value<< " ";
	if(current->right) inorder(current->right);
   }
   void inorder(){
      inorder(root);  
      cout<<endl;
   }
   void insert(int val){
	 root = insert(root, val);
   }
   void remove(int val){
	root = remove(root, val);
   }
};
class BSTIterative{
   Node *root=NULL;
   public:
   void insert(int val){
      if(!root){
	  root= new Node(val);
	  return;
      }
      Node *current=root;
      while(current){
	if(val < current->value){
	  if(current->left) current=current->left;
	  else{
	    current->left=new Node(val);
	    break;
	  }
	}
	else{
	  if(current->right)current=current->right;
	  else{
	    current->right=new Node(val);
	    break;
	  }
	}
      }
   }
   void inorder(Node *current){
	if(!current)return;
	if(current->left) inorder(current->left);
	cout <<current->value<< " ";
	if(current->right) inorder(current->right);
   }
   void inorder(){
      inorder(root);  
      cout<<endl;
   }
   void remove(int val){
      Node *current=root, *parent=NULL;
      while(current){
	if(val < current->value){
	 parent = current;
	 current = current->left;
	}else if(val > current->value){
	 parent = current;
	 current = current->right;
	}
	else{
	  if(current->left && current->right){
	    Node *tmp=current->right, *parTmp=current;
	    while(tmp->left)parTmp= tmp,tmp=tmp->left;

	    if(parTmp != current)
	      parTmp->left = tmp->right;
	    else
	      parTmp->right = tmp->right;
	    current->value=tmp->value;
	    delete tmp;
	  }else if(!parent){
	    if(current->left){
	      Node *tmp=current->left;
	      (*current) = *(tmp);
	      delete tmp;
	    }
	    else{
	      Node *tmp=current->right;
	      (*current) = (*tmp);
	      delete tmp;
	    }
	  }
	  else if(parent->left == current){
	    parent->left = (current->left)?current->left:current->right; 
	  }
	  else if(parent->right == current){
	    parent->right= (current->left)?current->left:current->right; 
	  }
	  break;
	}
      }
   }
};
int main(){
  BSTIterative bst;
  bst.insert(10);
  bst.insert(1);
  bst.insert(5);
  bst.insert(50);
  bst.inorder();
  bst.remove(10);
  bst.inorder();
  return 0;
  bst.remove(1);
  bst.remove(5);
  bst.remove(50);
  bst.remove(1);
  bst.remove(1);
  bst.inorder();
  return 0;
}
