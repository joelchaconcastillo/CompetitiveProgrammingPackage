#include <bits/stdc++.h>
using namespace std;
vector<vector<int>>st;
int n, k;
vector<int> lg;
void buildTableMin(vector<int> &data){
  n = data.size();
  lg.assign(n+1,0);
  lg[1]=0;
  for(int i =2; i<=n; i++) lg[i]=lg[i/2]+1;
  k = lg[n];
  st.assign(n+1, vector<int>(k+1,INT_MAX));
  for(int i = 0 ; i < n ; i++)st[i][0]=data[i];
  for(int j = 1; j <= k; j++){
    for(int i = 0; i+(1<<j) <= n; i++)
	    st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
  }
}
int queryMin(int L, int R){
   int j=lg[R-L+1]; 
   return min(st[L][j], st[R-(1<<j)+1][j]);
}
void buildTableSum(vector<int> &data){
  int n=data.size();
  lg.assign(n+1,0);
  lg[1]=0;
  for(int i = 2; i<=n; i++) lg[i]=lg[i/2]+1;
  k=lg[n];
  st.assign(n+1, vector<int> (k+1, 0));
  for(int i = 0; i < n ; i++) st[i][0]=data[i];
  for(int j = 1; j <=k; j++)
     for(int i=0; i + (1<<j) <=n; i++)
	st[i][j] = st[i][j-1] + st[i+(1<<(j-1))][j-1];

}
long long querySum(int L, int R){
    long long sum=0;
    int len=R-L+1;
    for(int j = k; j>=0; j--){
    // if((R-L+1) & (1<<j)) sum += st[L][j], L+=(1<<j);
     if(len & (1<<j)) sum += st[L][j], L+=(1<<j);
    }
    return sum;
}
int main(){
  ///testing...
  vector<int>data={1,2,3,-4,5,6,-78};
  buildTableMin(data);
  cout<<queryMin(5,5)<<endl;
  buildTableSum(data);
  cout<<querySum(4,6)<<endl;
   return 0;
}
