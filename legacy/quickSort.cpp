#include <bits/stdc++.h>
using namespace std;
int partition(vector<int> &data, int l, int r){
  int i=l-1;
  int pivot = data[r];
  for(int j=l; j < r; j++)
     if(data[j] < pivot) swap(data[j], data[++i]);
  swap(data[i+1], data[r]);
  return i+1;
}
void quickSort(vector<int> &data, int l, int r){
  if(l>=r)return;
  int pidx=partition(data, l, r);
  quickSort(data, l, pidx-1);
  quickSort(data, pidx+1,r);
}
int main(){
   vector<int> data{12,6,2,2,6,3,77,2};
   quickSort(data, 0, data.size()-1);
   for(auto i:data)cout<<i<<" ";
   cout<<endl;
   return 0;
}
