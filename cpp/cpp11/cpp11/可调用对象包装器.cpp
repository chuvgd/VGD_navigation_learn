#include <iostream>
#include <functional>

int add(int a , int b){
    std::cout<<a<<"+"<<b<<"="<<a+b<<std::endl;
    return a+b;
}

class T1{
    public:
        static int sub(int a,int b){
            std::cout<<a<<"-"<<b<<"="<<a-b<<std::endl;
            return a-b;
        }
};

class T2{
    public:
        int operator()(int a,int b){
            std::cout<<a<<"*"<<b<<"="<<a*b<<std::endl;
            return a*b;
        }
};

int print(int a, double b)
{
    std::cout << a << b << std::endl;
    return 0;
}


int main(){
    std::function<int(int,int)> f1 = add;
    //由于函数名表示其地址，其实包装完的对象就是一个函数指针，和函数指针的使用方式一致
    std::function<int(int,int)> f2 = T1::sub;
    //绑定仿函数
    T2 t;
    std::function<int(int,int)> f3 = t;
    //上述是对函数进统一包装可以进行同一方式调用

    // 定义函数指针
    int (*func)(int, double) = &print;
    func(520,13.14);
    
    //函数调用
    f1(9,3);
    f2(9,3);
    f3(9,3);

    return 0;
}