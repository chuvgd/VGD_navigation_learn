#include <iostream>

//引用作为重载条件
void func(int &a)
//int &a = 10;不合法——引用必须是对合法的内存
{
    std::cout<<"func(int &a)调用"<<std::endl;
}

void func(const int &a)
//const int &a = 10;合法——编译器优化
{
    std::cout<<"func(const int &a)调用"<<std::endl;
}

//函数重载遇到默认参数
void func2(int a,int b = 10){
    std::cout<<"func:a"<<std::endl;
}

void func2(int a){
    std::cout<<"func:b"<<std::endl;
}

int main(){
    int a = 10;//int a是非const左值(有名字，可以修改，有合法内存)
    func(a);//所以重载func(int &a)更优
    func(10);

    //func2(10);//有多个重载函数"func2"实例与参数列表匹配——二义性

    return 0;
}