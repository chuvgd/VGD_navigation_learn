#include <iostream>

void func(int &ref){
    //int &ref = a;
    ref = 100;//ref是引用，转化为*ref = 100
}

int main(){
    int a = 10;

    //自动转化为int* const ref = &a
    //指针常量是指针指向不可改变，但是指针指向的值可以改变——也体现了为什么引用可以重新赋值，但数不能改变引用
    int &ref = a;
    ref = 20;//自动转化成*ref = 20

    std::cout<<"a="<<a<<std::endl;
    std::cout<<"ref="<<ref<<std::endl;

    func(a);
    std::cout<<"a="<<a<<std::endl;

    return 0;
}