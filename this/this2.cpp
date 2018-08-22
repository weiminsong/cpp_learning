#include <iostream>
using namespace std;
class Demo {
	private:
		int num;
		char ch;
	public:
		void setMyValues(int num_set, char ch_set){
			//this->num =num;
			//this->ch=ch;
			num =num_set;
			ch=ch_set;
		}
		void displayMyValues(){
			cout<<num<<endl;
			cout<<ch<<endl;
		}
};
int main(){
	Demo obj;
	obj.setMyValues(100, 'A');
	obj.displayMyValues();
	return 0;
}
