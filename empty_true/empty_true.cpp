#include <iostream>
#include "empty_true.h"
void CaptureABC130_HCC_Pattern(bool byReset) {

  if(byReset){ std::cout<<"byReset is true"<<std::endl;}
  else{
      std::cout<<"byReset is false"<<std::endl;
  }
}
int main ( )
{
   CaptureABC130_HCC_Pattern();	
   return 0;
}
