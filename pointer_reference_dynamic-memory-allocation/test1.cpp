//http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/pass_by_address.html
#include <iostream>

using std::cout;
using std::endl;

void addToInt(int&);

int main()
{
	int num = 5;

	cout << "In main(), num is " << num << endl;
	cout << "In main(), address of num is " << (long int) &num << endl << endl;

	addToInt(num);

	cout << "In main(), value of num is now " << num << endl << endl;

	return 0;
}

void addToInt(int& numRef)
{
	cout << "In addToInt(), value of numRef is " << numRef << endl;
	cout << "In addToInt(), address of numRef is " << (long int) &numRef << endl;

	numRef += 10;

	cout << "In addToInt(), value of numRef is now " << numRef << endl << endl;
}
