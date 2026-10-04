#include<iostream>

using func_ptr = int(*)(int);
//类型别名——指向int(int)函数的指针,int是返回值类型，(int)是参数列表，是一个int类型参数
//没有捕获任何外部变量的匿名函数
func_ptr f = [](int a){
    return a;
};
//函数调用
int main(){
    f(1314);
    return 0;
}