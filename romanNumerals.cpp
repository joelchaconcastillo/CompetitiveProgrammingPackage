#include <bits/stdc++.h>
using namespace std;
string AtoR(int A){
  map<int, string> cvt;
  cvt[1000] = "M"; cvt[900]="CM"; cvt[500]="D"; cvt[400]="CD"; 
  cvt[100]="C"; cvt[90]="XC"; cvt[50]="L"; cvt[40]="XL";
  cvt[10]="X"; cvt[9]="IX"; cvt[5]="V"; cvt[4]="IV";
  cvt[1]="I";
  string Roman="";
  for(map<int, string> ::reverse_iterator i=cvt.rbegin(); i != cvt.rend(); i++){
    while(A>=i->first){
       Roman +=i->second;
       A -=i->first;
    }
  }
  return Roman;
}
int RtoA(string &R){
   map<char, int> RtoA;
   RtoA['I']=1; RtoA['V']=5; RtoA['X']=10; RtoA['L']=50;
   RtoA['C']=100; RtoA['D']=500; RtoA['M']=1000;
   int value = 0, n=R.size();
   for(int i = 0; i < n; i++){
       if( i+1 < n && RtoA[R[i+1]]>RtoA[R[i]]){
          value +=RtoA[R[i+1]] - RtoA[R[i]];
	  i++;
       }else value +=RtoA[R[i]];
   }
   return value;
}
int main(){

}
