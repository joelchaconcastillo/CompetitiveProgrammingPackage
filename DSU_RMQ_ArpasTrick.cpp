/*
 *The complexity of this is O((n+m)*alpha(n)) constant!!
 * a.k.a. Arpa's trick named after AmirReza Poorakhavan
 * */
#include <bits/stdc++.h>
using namespace std;
struct Query{
   int L, R, idx;
};
int n, m;
vector<vector<Query> > container;
vector<int> answer, parent, data;
int findSet(int v){
   if(v!=parent[v]){
     parent[v]=findSet(parent[v]); 
   }
   return parent[v];
}
void sol(){
   data = {1,0,0,4,2,1,3,-1,-19,100,4};
   n = data.size();
   parent.assign(n, 0);
   for(int i = 0 ; i < n; i++)parent[i]=i;
   answer.assign(n, 0);
   container.assign(n, vector<Query> ());
   vector<Query> q;
   q.push_back({0,5,0});
   q.push_back({2,5,0});
   q.push_back({3,5,0});
   q.push_back({4,7,0});
   m=q.size();
   for(int i = 0 ; i < m; i++){
      container[q[i].R].push_back({q[i].L,q[i].R,i});
   }
   stack<int> s;
   for(int i = 0 ; i < n; i++){
     while(!s.empty() && data[s.top()]>data[i]){
        parent[s.top()]=i;
	s.pop();
     }
     s.push(i);
     for(auto q:container[i]){
       answer[q.idx]= findSet(q.L);
     }
   }
   for(int i = 0 ; i < m; i++)cout<<answer[i]<<endl;
}
int main(){
 sol();
 return 0;
}
