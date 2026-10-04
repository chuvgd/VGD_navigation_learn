#include <iostream>

int main(){
    //野指针
    int* p = (int*)0x1100;

    std::cout<<*p<<std::endl;
    
    return 0;
}