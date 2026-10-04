#include <iostream>

void showValue(const int &ref){
    //ref = 100;//表达式必须是可修改的左值
    //让形式参数变成只可读，不能让形式参数直接修改实际参数（地址传递和引用传递都可以做到形式参数直接修饰实际参数）
    std::cout<<"val="<<ref<<std::endl;
}

int main(){
    int a = 10;
    int &ref = a;//引用必须引用一块合法的内存空间
    //int &ref1 = 10;//非常量引用的初始值必须为左值(编辑器解释)
    const int &ref2 = 10;//加上const之后，编译器将代码修改 int temp = 10;const int &ref = temp;
    //ref2 = 20;//表达式必须是可修改的左值，加上const之后，变成只读不可修改
    showValue(a);

    return 0;
}