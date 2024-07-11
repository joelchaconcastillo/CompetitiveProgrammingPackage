#include<bits/stdc++.h>
using namespace std;
vector<int> CountingSort(vector<int> &data){
  int n = data.size(), maxv=-INT_MAX;
  for(auto i:data)maxv=max(maxv, i);
  vector<int> freq(maxv+1,0), res(n, 0);
  for(auto i:data)freq[i]++;
  for(int i = 1; i < freq.size(); i++) freq[i] +=freq[i-1];
  for(int i = 0 ; i < n; i++) res[--freq[data[i]]] = data[i];
  return res;
}
int main(){
  vector<int> data {4,6,9,4};	
  auto res=CountingSort(data);
  for(auto i:res)cout << i <<" " <<endl;
  return 0;
}
