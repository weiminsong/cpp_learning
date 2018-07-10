//https://www.ntu.edu.sg/home/ehchua/programming/cpp/cp4_PointerReference.html
#include <iostream>

using std::cout;
using std::endl;

void addToInt(int*);

int main()
{
// Dynamic Allocation
	int * p2;            // Not initialize, points to somewhere which is invalid
	cout << p2 << endl; // Print address before allocation
	p2 = new int;       // Dynamically allocate an int and assign its address to pointer
	// The pointer gets a valid address with memory allocated
	*p2 = 99;
	cout << p2 << endl;  // Print address after allocation
	cout << *p2 << endl; // Print value point-to
	delete p2;           // Remove the dynamically allocated storage, the c++ will not complain if you do not free the memory here, but a potential memory leakage is there
	return 0;
}
