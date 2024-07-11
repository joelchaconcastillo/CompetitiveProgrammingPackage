#include <bits/stdc++.h>
using namespace std;
vector<int> prefixFunction(string &p){
  int n = p.size();
  vector<int> prefix(n+1, 0);
  prefix[0]=-1;
  int i=0, j =-1;
  while(i<n){
     while(j>=0 && p[j]!=p[i]) j = prefix[j];
     i++,j++;
     prefix[i]=j;
  }
  return prefix;
}
vector<int> goodSuffixShift(string p){
  auto m = p.size();
  vector<int> gs(m, m);
  vector<int>resets = prefixFunction(p);
  reverse(p.begin(), p.end());
  vector<int> resets_rev = prefixFunction(p);
  for(int j = 0; j < m; j++) gs[j] = m-1-resets[m-1];
  gs[m-1]=1;
  for(int l = 1; l < m; l++){
     int j = m-1-resets_rev[l];
     gs[j] = min(gs[j],l-resets_rev[l]);
  }
  return gs;
}
unordered_map <char, int> badRule(string &S, string &P){
   int n = S.size(), m = P.size();
   unordered_map<char, int> occurrenceLeft;
   for(int i = 0 ; i < m; i++) occurrenceLeft[P[i]]=i;
   for(int i = 0 ; i < n ; i++) 
      if(occurrenceLeft.find(S[i]) == occurrenceLeft.end()) 
         occurrenceLeft[S[i]]=-1;
   return occurrenceLeft;
}

void boyerMoore(string &S, string &P){
   int n = S.size(), m = P.size();
   vector<int> gs=goodSuffixShift(P);
   auto occurrenceLeft=badRule(S, P);
   int shift = 0;
   while(shift <= (n-m)){
      int j = m-1;
      while( j>=0 && P[j] == S[j+shift]) j--;
      if(j==-1){
	  cout << "found.. pos: " << shift<<endl;
          shift += max(gs[0], j-occurrenceLeft[S[shift]]);
      }
      else shift += max(gs[j], j-occurrenceLeft[S[shift+j]]);
   }
}
int main(){
   string S="GCAATGCCTATGTGACC", P="TATGTG";
   boyerMoore(S, P);
   S="ABAABABACBA", P="CABAB";
   boyerMoore(S, P);
   S="AABABABACBA", P="ABBAB";
   boyerMoore(S, P);
   S="ABAABABACBA", P="CABRABDAB";
   boyerMoore(S, P);

   return 0;
}
