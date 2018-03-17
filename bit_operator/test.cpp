#include<iostream>
using namespace std;
int main(){
	int a=0x00000000;
	int intVar=15;
	a &= ~0x0000001f;// ~ means get the opposite
	a |= ((intVar & 0x1f) << 0);
	cout<<a<<endl;
}
