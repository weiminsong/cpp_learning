#include <iostream>
using std::cout;
using std::endl;

#include <vector>    // vector class-template definition
#include <algorithm> // copy algorithm
#include <iterator>  // ostream_iterator iterator
#include <stdexcept> // out_of_range exception

int main()
{
	std::vector<int>  numbers;
	numbers.resize(5);
	numbers[0]=0;
	std::cout<<numbers[0]<<std::endl;
	std::cout<<numbers[4]<<std::endl;
	return 0;
}
