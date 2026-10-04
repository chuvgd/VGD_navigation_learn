#include <iostream>

//占位参数：只写数据类型，不写具体左值，但是调用函数传入参数时需要传入实际参数
//占位参数还可以有默认参数
void func(int a , int = 10){
    std::cout<<"this is func"<<std::endl;
}

int main(){
    func(10);

    return 0;
}