#include <bits/stdc++.h>
#define MAXS 100000
using namespace std;

template< class TPriority, class TKey > class heap{
    int realSize=0;
    vector<pair<TPriority, TKey> > tree; //starting with idx=1 is better!!
    unordered_map<TKey, int> state; //hashmap O(k)

  public:
    heap(){
       tree.assign(MAXS, pair<TPriority, TKey> (0, ""));
    }
    pair<TPriority, TKey> top(){ //O(1)
	if(realSize<1)return make_pair(-1, "-1");
        return tree[1];
    }
    void heapify_down(int idx){
	int maxidx = idx;
	while(2*idx<=realSize){
	   if(2*idx <= realSize && tree[maxidx] < tree[2*idx]) maxidx=2*idx;
	   if(2*idx+1 <= realSize && tree[maxidx] < tree[2*idx+1]) maxidx=2*idx+1;
	   if(idx==maxidx)break;
	   swap(state[tree[maxidx].second], state[tree[idx].second]);
	   swap(tree[maxidx], tree[idx]);
	   idx=maxidx;
	}
    }
    void heapify_up(int idx){ 
	 int p=idx/2;
	 while(p && tree[p] < tree[idx]){
	   swap(state[tree[p].second], state[tree[idx].second]);
	   swap(tree[p], tree[idx]);
	   idx=p; 
	   p=idx/2;
	 }
    }
    void pop(){ //O(1)
      if(realSize<1)return;
      swap(tree[1], tree[realSize]);
      state[tree[1].second]=1;
      state.erase(tree[realSize].second);
      realSize--;
      heapify_down(1);
    }
    void insert(const TPriority p, const TKey k){ //O(log n)
      realSize++;
      tree[realSize]=make_pair(p, k); 
      state[k]=realSize; 
      heapify_up(realSize);
    }
    void insertOrUpdate(const TPriority p, const TKey k){ //O(log n)
	if(state.find(k)==state.end()){
	   insert(p, k);
	   return;
	}
        int idx = state[k];
	tree[idx]=make_pair(p, k);
	heapify_down(idx);
	heapify_up(idx);
    }
    void erase(const TKey &k){ //O(log n)
	if(state.find(k) == state.end())return;
	int idx=state[k];
	swap(tree[idx], tree[realSize]);
	state[tree[idx].second] = idx;
	state.erase(k);
	realSize--;
	heapify_up(idx);
	heapify_down(idx);
    }
    bool isInserted(const TKey &k){ //O(1)
       return (state.find(k) != state.end());
    }
    int getSize(){ //O(1)
       return realSize;
    }
};
int main(){

   heap <int, string> h;
   int OP;
   cin>>OP;
   while(OP--){
     string st;
     cin>>st;
     if(st=="P"){
	auto o = h.top();
	if(h.top().first == -1)cout<<-1<<endl;
	else
	cout<<h.top().second<< " " << h.top().first<<endl;
     }
     else if(st=="IU"){
	string dish;
	int pr;
	cin>> dish >> pr;
	h.insertOrUpdate(pr, dish);
     }
     else if(st == "DL"){
	h.pop();
     }
     else if(st == "D"){
	string dish;
	cin>>dish;
	h.erase(dish);
     }
   }
   return 0;
}
