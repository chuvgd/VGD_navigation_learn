#include <iostream>

int func(int a , int b , int c){
    return a+b+c;
}

//函数默认参数
//如果我们自己传入数据（实际参数），就用自己的数据，如果没有就用默认
int func1(int a , int b = 20 , int c = 30){
    return a+b+c;
}

int func2(int a = 10,int b = 20);

//注意：声明和实现只能有一个默认参数
int func2(int a,int b){
    return a+b;
}

int main(){
    std::cout<<func(10,20,30)<<std::endl;

    std::cout<<func1(10,30)<<std::endl;

    std::cout<<func2(10,30)<<std::endl;

    return 0;
}