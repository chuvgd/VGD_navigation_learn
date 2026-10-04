#include <iostream>
void modify(const char* str)//在只有数组名的情况下，数组名退化成指向数组首地址的指针
{
    //const_cast是转换原本不是const类型的变量的const属性
    char* p = const_cast<char*>(str);
    //p指针是指向同一块数组的内存地址，但是是可以修改的内存地址
    //因为修改的是同一块内存地址，即修改的都是传入的实际参数所在的内存地址——main中的str[]数组的首地址
    p[0] = 'H';
}

int main(){
    char str[] = "hello";
    modify(str);
    std::cout<<"Modified str:"<<str<<std::endl;
    return 0;
}