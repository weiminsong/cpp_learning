#include <vector>
#include <iostream>
#include <algorithm>
int main(){
	int a[] = { 1, 2, 3, 4, 5 };
	std::vector<int> v(a, a+5);
	for (int i=0; i<5; i++){
		std::cout<<v[i]<<"	";}
	std::cout<<std::endl;
	//std::reverse(v.begin(), v.end());
	std::vector<int>v_rev(v.rbegin(), v.rend());
	for (int i=0; i<5; i++){
		std::cout<<v_rev[i]<<"	";}
	std::cout<<std::endl;
}
