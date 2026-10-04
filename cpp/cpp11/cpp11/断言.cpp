#include <iostream>
#include <cassert>
#include <cstring>

//创建一个指定大小的char类型数组
char* creatArray(int size){
    //通过断言判断数组大小是否大于0
    assert(size>0);//必须大于0,否则程序中断
    char* array = new char[size];
    return array;
}

int main(){
    char* buf = creatArray(0);
    //strcpy()函数声明：char* strcpy(char* dest , const char* src)
    //dest--指向用于存储复制内容的目标数组 //src--要复制的字符串 //返回值：返回一个指向最终的目标字符串dest指针
    strcpy(buf , "hello,world!");
    std::cout<<"buf = "<<buf<<std::endl;
    delete[] buf;
    return 0;
}