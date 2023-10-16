/*
 * Note that x refers to the rows and y refers to the cols, even thouh it
 * is counter intuitive..
 * */
#include <bits/stdc++.h>
#define NA 0
using namespace std;
class SegmentTree2D{
  int rows, cols;
  int left(int p){return p<<1;}
  int right(int p){return (p<<1)+1;}
  public:
  vector<vector<int> > data, tree;
   SegmentTree2D(int n, int m){
      rows=n, cols=m;
      data.assign(rows, vector<int> (cols, NA));
      tree.assign(4*rows, vector<int> (4*cols, NA));
   }
   void build_y(int nodex, int Lx, int Rx, int nodey, int Ly, int Ry){
    if(Ly==Ry){
      if(Lx==Rx) tree[nodex][nodey]=data[Lx][Ly];
      else tree[nodex][nodey] = tree[left(nodex)][nodey]+tree[right(nodex)][nodey];
    }else{
       int my = (Ly+Ry)/2;
       build_y(nodex, Lx, Rx, left(nodey), Ly, my);
       build_y(nodex, Lx, Rx, right(nodey), my+1, Ry);
       tree[nodex][nodey]=tree[nodex][left(nodey)]+tree[nodex][right(nodey)];
    }
   }	
   void build_x(int nodex, int Lx, int Rx){
     if( Lx!=Rx){
	int mx=(Lx+Rx)/2;
	build_x(left(nodex), Lx, mx);
	build_x(right(nodex), mx+1, Rx);
     }
     build_y(nodex, Lx, Rx, 1, 0, rows-1);
  }
  int sum_y(int nodex, int nodey, int Ly, int Ry, int iy, int jy){
      if(jy < Ly || iy >Ry ) return NA; 
      if(Ly>=iy && jy>=Ry) return tree[nodex][nodey];
      int my = (Ry+Ly)/2;
      return sum_y(nodex, left(nodey), Ly, my, iy, jy)
	      +sum_y(nodex, right(nodey), my+1, Ry, iy, jy);
  }
  int sum_x(int nodex,int Lx, int Rx, int ix, int jx, int iy, int jy){
      if(jx < Lx || ix >Rx ) return NA; 
      if(Lx>=ix && jx>=Rx) return sum_y(nodex, 1, 0, rows-1, iy, jy);
      int mx = (Lx+Rx)/2;
      return sum_x(left(nodex), Lx, mx, ix, jx, iy, jy)
	      +sum_x(right(nodex),mx+1, Rx, ix, jx, iy, jy);
  }
  void update_y(int nodex, int Lx, int Rx, int nodey, int Ly, int Ry, int x, int y, int val){
   if(Ly==Ry){
      if(Lx==Rx) tree[nodex][nodey]=val;
      else tree[nodex][nodey]=tree[left(nodex)][nodey]+tree[right(nodex)][nodey];
   }else{
      int my=(Ly+Ry)/2;
      if(y<=my) update_y(nodex, Lx, Rx, left(nodey), Ly, my, x, y, val);
      else update_y(nodex, Lx, Rx, right(nodey), my+1, Ry,x,y, val);
      tree[nodex][nodey]=tree[nodex][left(nodey)]+tree[nodex][right(nodey)];
   }
  }
  void update_x(int nodex, int Lx, int Rx, int x, int y, int val){
   if(Lx!=Rx){
     int mx=(Lx+Rx)/2;
     if(x<=mx) update_x(left(nodex), Lx, mx, x, y, val);
     else update_x(right(nodex), mx+1, Rx, x, y, val);
   }
   update_y(nodex, Lx, Rx, 1, 0, rows-1, x, y, val);
  }
   int query(int ix, int jx, int iy, int jy){
	   return sum_x(1, 0, cols-1, ix, jx, iy, jy);
   }
   void build(){
     build_x(1, 0, cols-1);
   }
   void update(int x, int y, int v){
	   update_x(1, 0, cols, x, y, v);
   }
};
int main(){
   SegmentTree2D st2d(3, 3);
   for(auto &r:st2d.data){
	for(auto &i:r) i=rand()%10;
   }
   st2d.build();
   for(auto &r:st2d.data){
	for(auto &i:r) cout<<i<<" ";
	cout<<endl;
   }
   cout<< st2d.query(0,1, 0, 2)<<endl;
   return 0;
}
