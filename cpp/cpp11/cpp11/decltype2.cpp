//表达式是函数调用，使用decltype推导出的类型和函数返回值一致
#include <iostream>
#include <string>

class Test{};

//函数声明
int func_int();
int& func_int_r();
int&& func_int_rr();

int main(){
//decltype类型推导
int n = 100;
decltype(func_int()) a = 0;
decltype(func_int_r()) b = n;
decltype(func_int_rr()) c = 0;

return 0;
}