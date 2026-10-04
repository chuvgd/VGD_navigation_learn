#include <iostream>

class Base{
    public: 
        int a;
        Base(int v) : a(v){};
        virtual ~Base() = default;
};

class Derived : public Base {
    public:
        int b;
};

int main(){
    Base d(10);

    Derived* p = static_cast<Derived*>(&d);
    std::cout<<p->b<<std::endl;

    return 0;
}

//这里可以看到进行向下的类型转换后是获取不到派生类的成员
//原因：子类的内存比父类大，如果直接从父类转换成子类的对象，会导致没有相关子类成员的地址，无法直接访问