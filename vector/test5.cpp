#include <iostream>
using std::cout;
using std::endl;

#include <vector>    // vector class-template definition
#include <algorithm> // copy algorithm
#include <iterator>  // ostream_iterator iterator
#include <stdexcept> // out_of_range exception

int main()
{
	std::vector<int>  *numbers = new std::vector<int>;
	//(*numbers).push_back(5);
	//(*numbers).push_back(4);
	//(*numbers).push_back(3);
	//(*numbers).push_back(2);
	(*numbers)[0]=5;
	(*numbers)[1]=4;
	(*numbers)[2]=3;
	(*numbers)[3]=2;
	for(int n : *numbers) {
		std::cout << n << '\n';
	}
	return 0;
}
