#include <iostream>

class Base{
    public:
        int a;
};

class Derived : public Base{
    public:
        int b;
        Derived(int v): b(v){
            this -> a = v;
        }
};

int main(){
    Base b;
    //c语言风格转换将b强制转换为Derived*，相当于static_cast和reinterpret_cast的混合
    //没有运行时检查，可能导致未定义\
    //存疑，后续学完面向对象再来感受
    Derived* d = (Derived*)&b;
    std::cout<<"Derived pointer:"<<d -> a<<std::endl;

    
    return 0;
}