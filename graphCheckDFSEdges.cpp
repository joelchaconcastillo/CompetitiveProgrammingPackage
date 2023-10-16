#include <bits/stdc++.h>
#define UNVISITED 1
#define VISITED 2
#define EXPLORED 3

using namespace std;
vector<vector<int> > AdjList;
vector<int>dfs_num, dfs_parent;
void graphCheck(int u){
   dfs_num[u]=EXPLORED;
   for(auto nxt:AdjList[u]){
       if(dfs_num[nxt]==UNVISITED){
	  dfs_parent[nxt]=u;
          graphCheck(nxt);
       }
       else if(dfs_num[nxt]==EXPLORED){
          if(dfs_num[nxt]!=dfs_parent[nxt]){
	       cout<<"back-endge"<<endl;
	  }else{
		 cout<<"bidirectional edges!"<<endl;
	  }
       }
       else if(dfs_num[nxt]==VISITED){
	cout << "forward/cross edge"<<endl;
       }
   }
   dfs_num[u]=VISITED;
}
int main(){
   int n = 100;
   dfs_num.assign(n, UNVISITED);
   dfs_parent.assign(n, 0);
   graphCheck(0);
   return 0;
}
