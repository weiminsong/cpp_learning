// C++ Program to demonstrate working of break statement

#include <iostream>
using namespace std;
int main() {
    float number, sum = 0.0;

    // test expression is always true
    while (true)
    {
        cout << "Enter a number: ";
        cin >> number;
        
        if (number != 0.0)
        {
            sum += number;
        }
        else
        {
            // jump to the condition, and this will lead a dead loop 
            continue;
        }

    }
    cout << "Sum = " << sum <<endl;

    return 0;
}
