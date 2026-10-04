#include <iostream>

void printValue(int& i){
    std::cout<<"l-value:"<<i<<std::endl;
}

void printValue(int&& i){
    std::cout<<"r-value:"<<i<<std::endl;
}

void forward(int&& k){
    printValue(k);
    //函数forward()接收的一个右值，但是在这个函数中调用printValue()时，参数k变成一个命名对象，编译器当成左值来处理
}

int main(){
    int i = 520;
    printValue(i);
    printValue(1314);
    forward(250);

    return 0;
}