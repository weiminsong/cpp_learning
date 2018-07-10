#include <stdlib.h> 
#include <iostream> 
int main(){
	int i=system("mkdir -p ~/.yarr");
	std::cout<<i<<std::endl;
	std::string home = getenv("HOME");
	std::cout<<home<<std::endl;
}

