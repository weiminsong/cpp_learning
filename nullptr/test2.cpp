// C++ program to demontrate problem with NULL
#include <bits/stdc++.h>
using namespace std;
 
// function with integer argument
int fun(int N)   { cout << "fun(int)" <<endl; }
 
// Overloaded function with char pointer argument
int fun(char* s)  { cout << "fun(char *)" <<endl; }
 
int main() 
{
    // Ideally, it should have called fun(char *),
    // but it causes compiler error.
    fun(nullptr);  
    fun(3);  
    int x=NULL;
    fun(x);  
}
