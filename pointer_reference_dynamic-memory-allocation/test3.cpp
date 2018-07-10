//http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/pass_by_address.html
#include <iostream>

using std::cout;
using std::endl;

void addToInt(int*);

int main()
{
	int num = 5;

	cout << "In main(), value of num is " << num << endl;
	cout << "In main(), address of num is " << (long int) &num << endl << endl;

	addToInt(&num);

	cout << "In main(), value of num is now " << num << endl << endl;   

	return 0;
}

void addToInt(int* ptr)
{
	cout << "In addToInt(), value of ptr is " << (long int) ptr << endl;
	cout << "In addToInt(), address of ptr is " << (long int) &ptr << endl;
	cout << "In addToInt(), value of variable pointed to by ptr is " << *ptr << endl << endl;

	*ptr += 10;

	cout << "In addToInt(), value of variable pointed to by ptr is now " << *ptr << endl << endl;
}
