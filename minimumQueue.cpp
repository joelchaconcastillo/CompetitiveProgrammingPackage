#include <bits/stdc++.h>
using namespace std;
/*
 *Method 1..
 * */
void add(deque<int> &q, int value){
  while(!q.empty() && value < q.back()) q.pop_back();
  q.push_back(value);
}
int getMinimum(deque<int> &q){
   return q.front();
} 
void remove(deque<int>&q, int value){
   if(!q.empty() && q.front()==value)q.pop_front();
}
/**
 *Method 2..
 * */
int cnt_added=0, cnt_removed=0;
void add2(deque<pair<int,int>> &q, int value){
  while(!q.empty() && q.back().first>value)q.pop_back();
  q.push_back({value, cnt_added});
  cnt_added++;
}
int getMinimum2(deque<pair<int,int>> &q){
   return q.front().first;
}
void remove(deque<pair<int,int>> &q){
    if(!q.empty() && q.front().second==cnt_removed)
	    q.pop_front();
    cnt_removed++;
}
/***
 *Method 3...
 * */
stack<pair<int, int> > s1,s2;
int getMinimum3(){
    if(!s1.empty() && !s2.empty())
	    return min(s1.top().second, s2.top().second);
    if(!s1.empty()) return s1.top().second;
    if(!s2.empty())return s2.top().second;
    return -1;
}
void add3(int value){
   int minimum = value;
   if(!s1.empty()) minimum=min(minimum, s1.top().second;
   s1.push({value, minimum});
}
void remove3(){
   if(s2empty()){
      while(!s1.empty()){
	auto element = s1.top().first; s1.pop();
	int minimum = element;
	if(!s2.empty()) minimum=min(minimum, s2.top().second);
	s2.push({element, minimum});
      }
   }
   int remove_element = s2.top().first;
   s2.pop();
}
int main(){
   return 0;
}
