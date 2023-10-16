#include <bits/stdc++.h>
using namespace std;
int main(){
  string st="AAAAABBCCE";
  int n = st.size();
  map<char, int> rep;
  int maxCount =-INT_MAX;
  for(auto i:st){
	  rep[i]++;
	  maxCount =max(maxCount, rep[i]);
  }
  vector<pair<int, char> > items;
  for(auto i:rep) items.push_back({-i.second, i.first});
  sort(items.begin(), items.end());
  vector<string> buckets(maxCount, "");
  cout << maxCount<<endl;
  for(int i = 0, k=0; i <items.size(); i++){
     for(int j = 0; j < -items[i].first; j++){
        buckets[k] +=items[i].second;
	k = (k+1)%maxCount;
     }
  }
  string result="";
  for(int i = 0; i < buckets.size(); i++) result +=buckets[i];
  cout << result<<endl;
  return 0;
}
