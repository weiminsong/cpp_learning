// thread example 
// http://www.cplusplus.com/reference/thread/thread/
#include <iostream>       // std::cout
#include <thread>         // std::thread
 
void foo() 
{
	for (int i=0; i<10; i++){
		std::cout<<"I am in foo(), and I am counting to "<<i<<std::endl;
	}
}

void bar(int x)
{
	for (int i=10; i>0; i--){
		std::cout<<"I am in bar(), and I am counting to "<<i<<std::endl;
	}
}

int main() 
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
