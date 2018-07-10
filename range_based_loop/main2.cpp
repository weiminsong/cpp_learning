#include <iostream>
#include <vector>

int main() {
	std::vector<int> v = {0, 1, 2, 3, 4, 5};

	for (int& i : v){ // access by const reference
		std::cout << i << ' ';
		i++;
	}
	std::cout <<'\n';

	for (const int& i : v) // access by const reference
		std::cout << i << ' ';
	std::cout <<'\n';

}
