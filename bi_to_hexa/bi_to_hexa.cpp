#include <iostream>
#include <bitset>
using namespace std;

int main(){
   int a=0x00333334;
   cout<<bitset<32>(a)<<endl;
   int b=0x00333134;
   cout<<bitset<32>(b)<<endl;
}
