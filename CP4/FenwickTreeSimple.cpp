#include <bits/stdc++.h>
using namespace std;
#define LSOne(S) ((S) & (-S))

typedef vector<int> vi;

class FenwickTree{
  private:
    vi ft;
  public:
    FenwickTree(int m){ ft.assign(m+1, 0); }
    int rsq(int j){
      int sum = 0;
      for(; j; j -= LSOne(j)) sum += ft[j];
      return sum;
    }
    int rsq(int i, int j){
       return rsq(j) - rsq(i-1);
    }
    void update(int i, int v){
       for(; i < (int)ft.size(); i+=LSOne(i)) ft[i] +=v ;
    }
};
int main(){
   FenwickTree FT(10);
   FT.update(9, 10);
   FT.update(8, 10);
   cout << FT.rsq(1, 10)<<endl;
   return 0;
}
