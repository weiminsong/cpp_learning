#include <iostream>
#include <string>
int main(){
std::string a="a";
int b=std::stoi(a,nullptr,2);
std::cout<<b<<std::endl;
}
