#include <iostream>
using namespace std;

int main()
{
	auto sum = [](int x, int y) { return x + y; };
	cout << sum(5, 2) << endl;
	cout << sum(10, 5) << endl;
}
