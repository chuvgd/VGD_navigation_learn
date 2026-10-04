#include <iostream>

int main(){
    int* p = NULL;

    //空指针是不可以进行访问的
    //0～255之间的内存编号是系统占用的,因此是不可访问的
    *p = 100;

    return 0;
}