// God & me
// "Someone like you"?! Unbelievable ... 
#include <bits/stdc++.h>
using namespace std;


const int maxn = 1e5 + 17;
int par[maxn], ans[maxn], n, a[maxn], l[maxn], q;
vector<int> qu[maxn];
int root(int v){
    return par[v] == -1 ? v : par[v] = root(par[v]);
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    memset(par, -1, sizeof par);
    cin >> n;
    for(int i = 0; i < n; i++)  cin >> a[i];
    cin >> q;
    for(int i = 0, r; i < q; i++){
	cin >> l[i] >> r, r--, l[i]--;
	qu[r].push_back(i);
    }
    stack<int> st;
    for(int i = 0; i < n; i++){
	while(st.size() && a[st.top()] <= a[i])
	    par[st.top()] = i, st.pop();
	st.push(i);
	for(auto qi : qu[i])
	    ans[qi] = a[root(l[qi])];
    }
    for(int i = 0; i < q; i++)
	cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}
