#include <iostream>

//函数重载
//可以让函数名相同，提高复用性
//条件：1.同一个作用域下——目前全在全局作用域下
//2.函数名称相同
//3.函数参数类型不同，或者个数不同，或者顺序不同

void func(int a){
    std::cout<<"func的调用:"<<std::endl;
}

void func(double a){
    std::cout<<"func的调用:?"<<std::endl;
}

void func(){
    std::cout<<"func的调用:!"<<std::endl;
}

void func(int a,double b){
    std::cout<<"func的调用:."<<std::endl;
}

void func(double b,int a){
    std::cout<<"func的调用:+"<<std::endl;
}

// int func(double a,int b){
//     std::cout<<"func的调用:-"<<std::endl;
// }
//编译器解释：无法重载仅按返回类型区分的函数

int main(){
    //func();
    func(10);

    func(10.0);

    func(10,10.0);

    func(10.0,10);

    return 0;
}

//注意事项：函数的返回值不可以作为函数重载的条件