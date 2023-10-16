#include <bits/stdc++.h>
using namespace std;
void merge(vector<int> &data, int l, int m, int r){
   int i = l, j=m+1, s=0;
   vector<int> tmp(r-l+1);
   while(i <= m && j <= r){
      if(data[i] < data[j])tmp[s]= data[i], i++;
      else tmp[s]=data[j], j++;
      s++;
   }
   while(i<=m) tmp[s]=data[i], i++, s++;
   while(j<=r) tmp[s]=data[j], j++, s++;
   for(int ii=l, jj=0; ii <=r; ii++, jj++) data[ii]=tmp[jj];  
}
void mergeSort(vector<int>&data, int l, int r){
   if(l>=r)return;
   int m=(l+r)/2;
   mergeSort(data, l, m);
   mergeSort(data, m+1,r);
   merge(data, l, m, r);
}
int main(){
  vector<int> data{1,5,3,2,5,42};
  mergeSort(data, 0, data.size()-1);
  for(auto i:data)cout <<i<<" ";
  cout<<endl;
}
