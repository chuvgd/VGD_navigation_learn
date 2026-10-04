#include <iostream>

void func(const int num){
    const int count = 24;
    int array[num]; //error，num是一个只读变量，不是常量
    int array1[count]; //ok,count是一个常量

    int a1 = 520;
    int a2 = 250;
    const int& b = a1;
    //左值引用只能绑定左值
    //但是左值引用只读可以直接绑定右值
    // const int& a = 123;
    // b = a2;//error
    a1 = 1314;
    std::cout<<"b:"<<b<<std::endl;
}
//void func(const int num)的参数num表示这个变量是只读的，但不是常量
//const int count = 24中的count是一个常量
//变量只读并不等价于常量
//左值引用只读，就比如说b是只读的，但是并不保证它的值是不可改变的，也就是说它不是常量

int main(){
    func(10);

    return 0;
}