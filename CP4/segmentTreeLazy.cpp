#include <bits/stdc++.h>
#define NA -1
using namespace std;

typedef vector<int> vi;

class SegmentTree{
  private:
    int n;
    vi A, st, lazy;
    int l(int p){ return p<<1;}
    int r(int p){ return (p<<1)+1;}

    int conquer(int a, int b){
      if(a == NA) return b;
      if(b == NA) return a;
      return min(a, b);
    }
    void build(int p, int L, int R){
       if(L==R) st[p] = A[L];
       else{
         int M = (L+R)/2;
	 build(l(p), L, M);
	 build(r(p), M+1, R);
	 st[p] = conquer(st[l(p)], st[r(p)]);
       }
    }
    void propagate(int p, int L, int R){
      if(lazy[p]!=NA){
	 st[p] = lazy[p];
	 if(L!=R) lazy[l(p)] = lazy[r(p)] = lazy[p];
	 else A[L] = lazy[p];
	 lazy[p] = NA;
      }
    }
    int RMQ(int p, int L, int R, int i, int j){
	propagate(p, L, R);
        if( j<L || i>R) return NA;
	if( L>=i && R<=j) return st[p];
	int M = (L+R)/2;
	return conquer( RMQ(l(p), L, M, i, j), 
			RMQ(r(p), M+1, R, i, j));
    }
    void update(int p, int L, int R, int i, int j, int val){
         if(j<L || i>R) return;
	 if( i<=L && R<=j){
	    lazy[p] = val;
	    propagate(p, L, R);
	    return;
	 }
	 int M = (L+R)/2;
	 update(l(p), L, M, i, j, val);
	 update(r(p), M+1, R, i, j, val);
	 st[p] = conquer(st[l(p)], st[r(p)]);
    }
  public:
    SegmentTree(int sz): n(sz), st(4*n), lazy(4*n, NA){}
    SegmentTree(const vi &initialA): SegmentTree((int) initialA.size()){
      A = initialA;
      build(1, 0, n-1);
    }
    void update(int i, int j, int val){update(1, 0, n-1, i, j, val);}
    int RMQ(int i, int j){ return RMQ(1, 0, n-1, i, j); }
};

int main(){
  vi A = {18, 17, 13, 19, 15, 11, 20, 99};
  SegmentTree st(A);
  cout << st.RMQ(1, 3)<<endl; //13
  cout << st.RMQ(4, 7)<<endl; // 11
  cout << st.RMQ(3, 4)<<endl; // 15
  st.update(5, 5, 77);
  cout << st.RMQ(1, 3)<<endl; //13 
  cout << st.RMQ(4, 7)<<endl; //15
  cout << st.RMQ(3, 4)<<endl; //15
  st.update(0, 3, 30);
  cout << st.RMQ(1, 3)<<endl; //
  cout << st.RMQ(4, 7)<<endl;
  cout << st.RMQ(3, 4)<<endl;
  st.update(3, 3, 7);
  cout << st.RMQ(1, 3)<<endl;
  cout << st.RMQ(4, 7)<<endl;
  cout << st.RMQ(3, 4)<<endl;


  return 0;
}
