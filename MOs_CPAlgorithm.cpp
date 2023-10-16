#include <bits/stdc++.h>
using namespace std;
int block_size, currentSum=0, n;
vector<int> A;
struct Query{
  int l, r, idx;
 bool operator <(Query other)const{
    return make_pair(l/block_size, r) < make_pair(other.l/block_size, other.r);
 } 
};
void add(int idx){
    currentSum +=A[idx];
}
void remove(int idx){
    currentSum -=A[idx];
}
int getAnswer(){
   return currentSum;
}
vector<int> mos_algorithm(vector<Query> &queries){
   sort(queries.begin(), queries.end());
   vector<int> ans(queries.size());
   int cur_l=0, cur_r=-1;
   for(auto q:queries){
      while(cur_l < q.l) remove(cur_l++);
      while(cur_l > q.l) add(--cur_l);
      while(cur_r < q.r) add(++cur_r);
      while(cur_r > q.r) remove(cur_r--);
      ans[q.idx]=getAnswer();
   }
   return ans;
}
int main(){
   A={1,3,4,5,67,4,5,6};
   n=A.size();
   block_size = sqrt(n)+1;
   vector<Query> q;
   q.push_back({0,2, 0});
   q.push_back({0,5, 1});
  auto ans = mos_algorithm(q);
   for(auto i:ans)cout<<i <<" ";
   return 0;
}
