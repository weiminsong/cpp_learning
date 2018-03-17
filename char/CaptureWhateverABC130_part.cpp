#include <iostream>
#include <stdio.h>
#include <vector>
int main(){
	std::vector<int> numbers={21,22,23,24,25};
	char buffer[100];
	buffer[0] = 0;
	int offset = 0;
	offset += sprintf(buffer, "Chips: ");
	for(size_t i=0; i<numbers.size(); i++) {
		offset += sprintf(buffer+offset, "%d ", numbers[i]);
		std::cout<<"offset	"<<offset<<std::endl;
		std::cout<<"buffer	"<<buffer<<std::endl;
	}
}
