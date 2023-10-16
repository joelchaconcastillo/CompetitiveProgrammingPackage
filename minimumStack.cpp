#include <bits/stdc++.h>
using namespace std;
void add(stack<pair<int,int>> &st, int value){
  if(st.empty()){
     st.push({value, value});
     return;
  }
  st.push({value, min(value, st.top().second)});
}
int getMin(stack<pair<int,int>> &st){
   return st.top().second;
}
int main(){
  stack<pair<int,int>> st;
  add(st, 100);
  add(st, -100);
  add(st, -1);
  cout<<getMin(st)<<endl;
  return 0;
}
