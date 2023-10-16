#include <bits/stdc++.h>
using namespace std;
int m=1e9+9,s, H=5;
vector<vector<long long> > p_pow, h;
vector<int> P;
int main(){
   string s1, s2;
   int k;
   cin>>s1>>k>>s2;
   s=s2.size();
   p_pow.assign(s, vector<long long> (H, 0));
   h.assign(s+1, vector<long long> (H, 0));
   P.assign(H, 1);
   for(int i = 0 ; i < H; i++)p_pow[0][i]=1, P[i]=rand();
   int finalCounter=0;
   unordered_map<int, bool> bad;
   map<vector<long long>, bool>counter;
   for(auto i:s1)bad[i]=true;
   for(int i = 1; i < s; i++)
	for(int j = 0; j < H ;j++)
	   p_pow[i][j] = (p_pow[i-1][j]*P[j])%m;

   for(int i = 0; i < s; i++){
	   for(int j = 0 ; j < H; j++)
	   h[i+1][j] = (h[i][j]+(s2[i]-'a'+1)*p_pow[i][j])%m;
   }
  for(int  i = 0; i < s; i++){//start...
     int countK=0;
   for(int l = 1; l+i <=s; l++){ //length
	if(bad[s2[i+l-1]])countK++;
	if(countK>k)break;
	vector<long long> keys(H,0);
	for(int j = 0;j < H; j++)
		keys[j]=(((h[i+l][j]-h[i][j]+m)%m)*p_pow[s-i-1][j])%m;
	if(counter.find(keys)==counter.end()){
	    finalCounter++;
	    counter[keys]=true;
	}
     }
   }
   cout<<finalCounter<<endl;

   return 0;
}
