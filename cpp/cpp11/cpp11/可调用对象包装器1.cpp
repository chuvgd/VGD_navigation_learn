#include <iostream>
#include <functional>

class A{
    public:
        //构造函数参数是一个包装器对象
        //初始化列表初始化成员变量callback，初始化函数指针指向
        //这里是传入一个包装器的函数指针对象，即传入的是一个函数的地址
        //回调函数
        A(const std::function<void()> &f):callback(f){};

        void notify(){
            callback();//调用通过构造函数得到的函数指针
        }
    private:
        std::function<void()> callback;
};

class B{
    public:
        //重载operator()运算符
        void operator()(){
            std::cout<<"我是要成为海贼王的男人!!!"<<std::endl;
        }
};

int main(){
    B vgd;
    vgd();//仿函数

    A RM(vgd);
    RM.notify();

    return 0;
}