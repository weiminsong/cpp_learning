#include<iostream>
using namespace std;
int main(){
	int a[2]={0x00000001,0xffffffff};
	for(int i=0; i<32; i++){
		int test=(a[0]<<i);
		cout<<a[0]<<endl;
		cout<<test<<endl;
	}
}
