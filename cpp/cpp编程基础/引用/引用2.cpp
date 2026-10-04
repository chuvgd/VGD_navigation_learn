#include <iostream>

int main(){
    int a = 10;

    int &b = a;

    int c = 20;

    //int &b = c;错误，初始化引用就不能更改引用了

    b = c;//赋值操作，而不是更改引用

    std::cout<<"a= "<<a<<std::endl;
    std::cout<<"b= "<<b<<std::endl;
    std::cout<<"c= "<<c<<std::endl;
    
    return 0;
}