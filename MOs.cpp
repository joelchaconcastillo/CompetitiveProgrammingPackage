/**
 *This version solves the standar MO's algorithm 
 *this implementation is for the problem "D-Query"
 *url: https://www.spoj.com/problems/DQUERY/
 * */
#include <bits/stdc++.h>
#define MAX_N 1111111
using namespace std;
int N, Q, currentAnswer, K=1;
struct query{
   int id, l, r, lBlock;
   bool operator <(const query& rhs){
	if(lBlock == rhs.lBlock){
	   return (r < rhs.r);
	}
        return (lBlock < rhs.lBlock);
   }
};
vector<query> queries;
vector<int> data, freq;
vector<bool> marked;
void process(int idx){
   if( marked[idx] && (--freq[values[idx]]==0)) _ans--;
    else if( (!marked[idx]) && (freq[values[idx]]++ == 0)) _ans++;
}
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cin>>N;
   data.assign(N, 0);
   freq.assign(MAX_N, 0);
   marked.assign(N, false);
   for(auto &i:data)cin>>i;
   cin>>Q;
   queries.assign(Q, query());
   int SQRT_N= sqrt(N)+1;
   for(int i = 0; i < Q; i++){
	   cin>> queries[i].l >> queries[i].r;
	   queries[i].l--;
	   queries[i].r--;
	   queries[i].id=i;
	   queries[i].lBlock=queries[i].l/SQRT_N;

   }
   sort(queries.begin(), queries.end()); 
   vector<int>ans(Q, 0);
   int cL=queries[0].l, cR=queries[0].l-1; 
   currentAnswer=0;
   for(int i = 0; i < Q; i++){
     auto &q=queries;
     int L=q[i].l, R=q[i].r;
     while(cL < q[i].l) process(cL++);
     while(cL > q[i].l) process(--cL);
     while(cR < q[i].r) process(++cR);
     while(cR > q[i].r) process(cR--);
     ans[q[i].id]=currentAnswer;
   }
   for(int i = 0; i < Q;i++)cout << ans[i]<<endl;

   return 0;
}
