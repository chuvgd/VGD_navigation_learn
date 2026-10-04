#include <iostream>

int main(){
    const int a = 10;//a本身是const属性，是常量
    int& b = const_cast<int&>(a);
    //b被绑定到a那块内存，语法上通过了；
    b = 20;
    //a的栈上内存实际上被写入了20
    //但是编译器已经把a折叠成了字面量10,所以打印出来的是10,不会去读内存
    //内存中确实是20,但是打印a时编译器是直接跳过内存，直接去打印字面量
    std::cout<<"转换后的a:"<< a <<std::endl;

    int a1 = (double)1.0;
    std::cout<<"转换后的a1:"<< a1 <<std::endl;

    return 0;
}

//cpp标准规定：修改一个真正的const对象就是未定义行为（UB）
//const int a = 10;a是定义良好的常量对象，值恒定为10
//通过const_cast强行修改，让整个程序行为进行未定义状态，而不是a变成未定义
