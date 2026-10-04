#include <iostream>

extern int a,b;
extern int c;
extern float f;

int main(){
    int a,b;
    int c;
    float f;
    a = 10;
    b = 20;
    c = a+b;

    std::cout<<c<<std::endl;

    f=70.0/3.0;
    std::cout<<f<<std::endl;

    return 0;
}

//这里强调一下有关声明和定义：
//声明——在c语言中建立存储空间的都是定义，反之是声明（声明是表示这个变量在其他作用域中存在，是被定义的，extern只是借用这个变量）
//定义——见上