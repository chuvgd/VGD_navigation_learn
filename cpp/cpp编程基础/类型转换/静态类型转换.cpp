#include <iostream>

class Base {
    public:
        int a;
        virtual ~Base(){};
};

class Derived : public Base {
    public:
        //继承了int a;
        int b;
        Derived(int v) : b(v) {
            this -> a = v;
        };
};

int main(){
    //static_cast只支持向上转换，即支持派生类向基类转换
    //原因：派生类继承自基类，内存更大，可以访问到基类的有对外接口的成员
    Derived d(10);
    Base b = static_cast<Base>(d);
    // Base* b = static_cast<Base*>(&d);
    std::cout << "Base pointer:" << b.a <<std::endl;
    // std::cout << "Base pointer:" << b->a <<std::endl;

    return 0;
}