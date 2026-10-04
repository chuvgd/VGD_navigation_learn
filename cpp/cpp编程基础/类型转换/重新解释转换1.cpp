#include <iostream>

int main(){
    int a = 10;
    //错误地将int*转换为double*
    double* p = reinterpret_cast<double*>(&a);
    //尝试以double*方式访问内存，可能破坏内存布局，导致未定义
    std::cout<<"*p="<<*p<<std::endl;

    return 0;
}