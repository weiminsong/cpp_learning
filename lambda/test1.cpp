#include <iostream>
using namespace std;

int main()
{
	auto lambda = []() { cout << "Code within a lambda expression" << endl; };
	lambda();
}
