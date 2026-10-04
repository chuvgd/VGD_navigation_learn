#include <iostream>
using namespace std;

int get100(){
    return 100;
}

int* fun(int&& rri)//右值引用作为函数形式参数
{
    rri = 0;
    std::cout<<"rri = "<<rri<<std::endl;
    return &rri;
}

int main(){
    int&& ri0 = 42;
    int&& ri1 = 'a';
    int&& ri2 = 1+2;
    
    //右值引用的内容可以进行修改
    ri0 = 1;
    cout<<"ri0 = "<<ri0<<endl;

    //虽然没有办法获取右值的地址，但是可以获取右值引用的地址，并通过地址修改值
    int* pi = &ri0;
    *pi = 2;
    cout<<"pi = "<<pi<<", *pi = "<<*pi<<", ri0 = "<<ri0<<endl;

    //传入右值，通过临时对象的返回把相关数据给接收对象
    int a = 3;
    int* p1 = fun(std::move(a));
    // int* p1 = fun(1+2);
    std::cout<<"这个右值引用的值修改之后的值："<<*p1<<std::endl;

    return 0;
}