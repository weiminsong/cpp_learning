#include<iostream>
int main(){
	for (int i=0; i<10; i++){
		std::cout<<i<<std::endl;
		//if (i>5) continue;
		if (i>5) break;
	}
}
