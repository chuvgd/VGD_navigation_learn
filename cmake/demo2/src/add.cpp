#include <stdio.h>
#include "head.h"
//"head.h"是指的是在./目录下（相对路径下）进行找相关头文件
//要么用上绝对路径，要么在cmake中指定头文件搜索路径(指定目录)

const char* libVersion = "Library Version 1.0";

int add(int a , int b){
    auto number = 8;
    return a+b+number;
}