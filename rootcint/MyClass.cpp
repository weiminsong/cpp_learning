#include <iostream.h>
#include "MyClass.h"

MyClass::MyClass()
{
   fX = -1;
   fY = -1;
}

void MyClass::Print() const
{
   cout << "fX = " << fX << ", fY = " << fY << endl;
}
//----
