#include <bits/stdc++.h>
using namespace std;
vector<int> strong_suffix(string &p){
     //strong suffix..
     int m=p.size(), i=m, j=m+1;
     vector<int> resetSuffix(m+1, 0), shift(m+1,-1);
     resetSuffix[i]=j;
     while(i>0){
       while(j<=m && p[i-1]!=p[j-1]){
	  if(shift[j-1]==-1) shift[j-1]=j-i;
	  j=resetSuffix[j];
       }
       i--, j--;
       resetSuffix[i]=j;
     }
     //prefix-suffix
     j=resetSuffix[0];
     for(i=0;i<=m;i++){
	if(shift[i]==-1) shift[i]=j;
	if(i==j) j=resetSuffix[j];
     }
     return shift;
}
unordered_map <char, int> badRule(string &S, string &P){
   unordered_map<char, int> occurrenceLeft;
   for(int i = 0; i < S.size(); i++) occurrenceLeft[S[i]]=-1;
   for(int i = 0 ; i < P.size(); i++) occurrenceLeft[P[i]]=i;
   return occurrenceLeft;
}
int BoyerMoore(string &S, string &P){
   int n = S.size(), m = P.size(), shift=0, count=0;
   auto gs = strong_suffix(P);
   auto occurrenceLeft=badRule(S, P);
   while( shift <= n-m){
      int j = m-1;
      while(j>=0 && P[j] == S[shift+j]) j--;
      if(j==-1){
	  count++;
	  shift += max(gs[0], j-occurrenceLeft[S[shift]]);
      }
      else shift += max(gs[j], j-occurrenceLeft[S[shift+j]]);
   }
   return count;
}
int main(){
   string s,p;
   cin>>p>>s;
   cout << BoyerMoore(s,p)<<endl;
   return 0;
}
