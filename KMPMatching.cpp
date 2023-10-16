#include <bits/stdc++.h>
using namespace std;
void matching1(string &s, string &pattern){
  int n = s.size(), m = pattern.size();
  vector<int> prefix(m+1, 0);
  prefix[0]=-1;
  int i = 0, j=-1;
  while(i < m ){
     j=prefix[i];
     while(j>=0 && pattern[i]!=pattern[j]) j = prefix[j];
     i++,j++;
     prefix[i] = j;
  }
  i = 0, j = 0;
  int count = 0;
  while(i < n){
     while(j >=0 && s[i]!=pattern[j]) j = prefix[j];
     i++,j++;
     if(j==m){
	count++;
	j = prefix[j];
     }
  }
  cout <<count<<endl;
}
void matching2(string &s, string &pattern){
   int m = pattern.size(), n = s.size();
   vector<int> prefix(m, 0);
   for(int i = 1; i < m; i++){
      int j = prefix[i-1];
      while(j>0 && pattern[i]!=pattern[j])j=prefix[j-1];
      if(pattern[i]==pattern[j])j++;
      prefix[i]=j;
   }
   int count = 0, j=0;
   for(int i = 0 ; i < n; i++){
      while(j>0 && s[i]!=pattern[j]) j=prefix[j-1];
      if(s[i]==pattern[j]) j++;
      if(j==m){
	count++;
	j = prefix[j-1];
      }
   }
   cout << count<<endl;
}
int main()
{
    string w="BLABLADEBLABLO", p="BLA"; 
    matching1(w, p);
    matching2(w, p);
    return 0;
}
