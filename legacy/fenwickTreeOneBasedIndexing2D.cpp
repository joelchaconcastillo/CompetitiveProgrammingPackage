#include <bits/stdc++.h>
using namespace std;
struct FenwickTree2D{
   vector<vector<int> > bit;
   int n, m;
   FenwickTree2D(int n, int m){
     bit.assign(n+1, vector<int>(m+1, 0));
   }
   FenwickTree2D(vector<vector<int> > &a){
       n=a.size(), m=a.front().size();
       bit.assign(n+1, vector<int>(m+1, 0));
       for(size_t i=0; i < a.size(); i++)
	for(size_t j=0; j < a[i].size(); j++)
	   add(i, j, a[i][j]);
   }
   int sum(int x1, int x2, int y1, int y2){
       x1++, x2++, y1++, y2++;
       return sum(y1, y2) - sum(x1-1,y2)-sum(y1, x2-1)+sum(x1-1, x2-1);
   }
   int sum(int x, int y){
      int ret=0;
     for(int i = x; i >0; i -= i&(-i))
	for(int j = y ; j>0; j -=j&(-j))
	   ret += bit[i][j];
     return ret;
   }
   void add(int x, int y, int delta){
      x++, y++;
      for(int i=x; i <= n; i += i&(-i))
	  for(int j=y; j<=m; j += j&(-j))
	    bit[i][j]+=delta; 
   }
};
int main(){
   vector<vector<int>>data={{1,1},{1,1},{2,2}};
   FenwickTree2D ft(data);
   cout <<ft.sum(0,0, 1,1)<<endl;
   cout <<ft.sum(0,0, 2,1)<<endl;
   cout <<ft.sum(1,0, 2,1)<<endl;
   return 0;
}
