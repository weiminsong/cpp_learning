#include <iostream>
#include <cstring>
int main(){

    std::cout<<"Please type the the name of your child?"<<std::endl;
    char* name=new char[30];

    int get_right_name=0;

    while (!get_right_name){

    std::cin>>name;

        if (strcmp(name,"shangshang")==0){
             std::cout<<"Aha, nice choice, and this chould be used as the infant name!"<<std::endl;
             std::cout<<"Please choose an official name again!"<<std::endl;
        }
        else if (strcmp(name,"lingxi")==0){
             std::cout<<"Excellent choice, and a girl named by this will be happy all the time!"<<std::endl;
             get_right_name=1;
        }
        else  {std::cout<<"En, just so so, please try again to get a better one!"<<std::endl;
        }
     }
}

