#include <bits/stdc++.h>
using namespace std;
vector<long long>a; 
unordered_map<int,int> val2Idx;
long long inv;
int n;
struct stNode{
    stNode*left, *right;
    long long count=0, value=0, subtreeSize=0;
};
vector<stNode> bagNodes(10000000);
int topBag=0;
class SegmentTreeCompressed{
   long long minv, maxv, TotalCount;
//   unordered_map<int, int> freq;
   stNode *root;
  public:
   SegmentTreeCompressed(){
      minv=0, maxv=2e5+1, TotalCount=0;
//      root=new stNode();
      root = &bagNodes[topBag++];
      bzero(root, sizeof(stNode));
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
	   //   freq[val]++;
	      return;
	   }
	   int m=(minValue+maxValue)/2;
	   if(val<=m){
	      //if(!current->left)current->left=new stNode();
	      if(!current->left)current->left=&bagNodes[topBag++], bzero(current->left, sizeof(stNode));
	      current=current->left;
	      maxValue=m;
	   }else{
	      //if(!current->right)current->right=new stNode();
	      if(!current->right)current->right=&bagNodes[topBag++], bzero(current->right, sizeof(stNode));
	      current=current->right;
	      minValue=m+1;
	   }
      }
   }
   //warning be sure that it exist before removing it...
   void erase(int val){
       auto current=root;
       int minValue=minv, maxValue=maxv;
//       if(freq[val]==0)return;
       while(true){
          current->subtreeSize--;
	  if( current->count!=0 && current->value==val){
	    current->count--;
	    //freq[val]--;
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

class SegmentTree{
   vector<SegmentTreeCompressed> st;
 //  vector<long long> data;
   int n;
   public:
      SegmentTree(vector<long long> &_a){
         n=_a.size();
//	 data=_a;
//	 st.assign(4*n, SegmentTreeCompressed());
	 st.resize(4*n);
//	 for(int i = 0 ;i < 4*n; i++){
//	    SegmentTreeCompressed stc;
//	    st.push_back(stc);
//	 }
      }
//      void build(int node, int L, int R){
//        if(L==R){
//          st[node].insert(data[L]);
//          return;
//        } 
//        int m=(L+R)/2;
//        build(node*2, L, m);
//        build(node*2+1, m+1, R);
//        for(int i = L ;i<=R; i++)st[node].insert(data[i]);
//      }

      void insert(int node, int L, int R, int idx, int oldVal, int newVal){
	  if(idx<L || idx>R)return;
          int m=(L+R)/2;
	  if(L!=R){
                insert(node*2, L, m, idx, oldVal, newVal);
                insert(node*2+1, m+1, R, idx, oldVal, newVal);
	  }
//	  st[node].erase(oldVal); 
          st[node].insert(newVal);
      }
      void remove(int node, int L, int R, int idx, int oldVal){
	  if(idx<L || idx>R)return;
          int m=(L+R)/2;
	  if(L!=R){
                remove(node*2, L, m, idx, oldVal);
                remove(node*2+1, m+1, R, idx, oldVal);
	  }
	  st[node].erase(oldVal); 
      }
      long long countLEQ(int node, int L, int R, int i, int j, int val){
           if(j<L || i>R)return 0;
           if(L>=i && j>=R) return st[node].countLEQ(val);
           int m=(L+R)/2;
           long long left=countLEQ(node*2, L, m, i, j, val);
           long long right=countLEQ(node*2+1, m+1, R, i, j, val);
           return left+right;
      }
      long long countGEQ(int node, int L, int R, int i, int j, int val){
           if(j<L || i>R)return 0;
	   if(i>j)return 0;
           if(L>=i && j>=R) return st[node].countGEQ(val);
           int m=(L+R)/2;
           long long left=countGEQ(node*2, L, m, i, j, val);
           long long right=countGEQ(node*2+1, m+1, R, i, j, val);
           return left+right;
      }
};
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int m;
   while(cin>>n>>m){
       inv=0;
       topBag=0;
       a.assign(n, 0);
       val2Idx.clear();
       SegmentTree st(a);
       for(int i = 0; i < n ; i++){
           cin>>a[i];
	   val2Idx[a[i]]=i;
	   inv += i-st.countLEQ(1, 0, n-1, 0, n-1, a[i]);
	   st.insert(1, 0, n-1, i, 0, a[i]);
       }
       for(int i = 0; i< m; i++){
	  cout<<inv<<endl;
          long long d;
	  cin>>d;
	  int left  = st.countGEQ(1, 0, n-1, 0, val2Idx[d]-1, d+1);
	  int right = st.countLEQ(1, 0, n-1, val2Idx[d]+1, n-1, d-1);
	  inv -=left+right;
	  st.remove(1, 0, n-1, val2Idx[d], d);
       }
   } 
   return 0;
}
