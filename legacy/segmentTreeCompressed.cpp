#include <bits/stdc++.h>
using namespace std;
struct stNode{
    stNode*left, *right;
    long long count=0, value=0, subtreeSize=0;
};
class SegmentTreeCompressed{
   long long minv, maxv, TotalCount;
   unordered_map<int, int> freq;
   stNode *root;
  public:
   SegmentTreeCompressed(){
      minv=0, maxv=2e5, TotalCount=0;
      root=new stNode();
   }
   void insert(int val){
      int minValue=minv, maxValue=maxv;
      auto current = root;
      while(true){
	   current->subtreeSize++;
	   if((current->count==0) || current->value==val){
              current->count++;
	      current->value=val;
	      TotalCount++;
	      freq[val]++;
	      return;
	   }
	   int m=(minValue+maxValue)/2;
	   if(val<=m){
	      if(!current->left)current->left=new stNode();
	      current=current->left;
	      maxValue=m;
	   }else{
	      if(!current->right)current->right=new stNode();
	      current=current->right;
	      minValue=m+1;
	   }
      }
   }
   //warning be sure that it exist before removing it...
   void erase(int val){
       auto current=root;
       int minValue=minv, maxValue=maxv;
       if(freq[val]==0)return;
       while(true){
          current->subtreeSize--;
	  if( current->count!=0 && current->value==val){
	    current->count--;
	    freq[val]--;
	    return;
	  }
	  int m=(minValue+maxValue)/2;
	  if(val<=m){
	    maxValue=m;
	    current=current->left;
	  }else{
	    minValue=m+1;
	    current=current->right;
	  }
       }
   } 
   long long countLEQ(int val){
     auto current=root;
     int minValue=minv, maxValue=maxv;
     long long total=0;
     while(current){
	 if(current->value<=val)total+=current->count;
	 int m=(minValue+maxValue)/2;
	 if(val<=m){
            current=current->left;
	    maxValue=m;
	 }else{
	    if(current->left)
	    total += current->left->subtreeSize;
	    current=current->right;
	    minValue=m+1;
	 }
     }
     return total;
   }
   long long countGEQ(int val){
     auto current=root;
     int minValue=minv, maxValue=maxv;
     long long total=0;
     while(current){
	 if(current->value>=val)total+=current->count;
	 int m=(minValue+maxValue)/2;
	 if(val<=m){
	    if(current->right)total+=current->right->subtreeSize;
            current=current->left;
	    maxValue=m;
	 }else{
	    current=current->right;
	    minValue=m+1;
	 }
     }
     return total;
   }
};

int main(){
  SegmentTreeCompressed st;
  vector<int> data={1,2,4,5,2,2,7,5,6,7,8};
  for(auto i:data)st.insert(i);
  cout<< st.countLEQ(7)<<endl;
  cout<< st.countLEQ(1)<<endl;
  cout<< st.countLEQ(8)<<endl;
  cout<< st.countLEQ(4)<<endl;
  cout<< st.countLEQ(-1)<<endl;
  st.erase(7);
  st.erase(7);
  st.erase(7);
  cout<< st.countLEQ(7)<<endl;
  cout<< st.countGEQ(7)<<endl;
  cout<< st.countGEQ(1)<<endl;
  cout<< st.countGEQ(4)<<endl;
  return 0;
}
