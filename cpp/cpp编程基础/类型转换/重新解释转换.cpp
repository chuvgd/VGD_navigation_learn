#include <iostream>
#include <cstdint>

int main(){
    int a = 42;
    //将指针转化为整数
    //typedef unsigned long uintptr_t
    uintptr_t addr = reinterpret_cast<uintptr_t>(&a);
    //再转换回指针
    int* p = reinterpret_cast<int*>(addr);
    std::cout<<"*p = "<<*p<<std::endl;

    return 0;
}

//