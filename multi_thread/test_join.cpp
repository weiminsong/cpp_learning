#include <iostream>
#include <thread>
#include <chrono>
 
void foo()
{
	for (int i=0; i<10 i++){
		// simulate expensive operation
		std::cout<<"I am in foo"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void bar()
{
	for (int i=0; i<10; i++){
		// simulate expensive operation
		std::cout<<"I am in bar"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);
 
    std::cout << "starting second helper...\n";
    std::thread helper2(bar);
 
    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}
