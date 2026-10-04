#include <iostream>

//指针类型的动态转换

class Base{
    public:
        virtual ~Base() = default;//基类必须有虚函数
};

class Derived : public Base{
    public:
    void show(){
        std::cout<<"Derived class method"<<std::endl;
    }
};

int main(){
    Base* ptr_base = new Derived;//基类指针指向派生类对象
    //父类的指针实际指向子类的实例，内存足够
    //如果这里是：
    //Base* ptr_base = new Base;
    //内存上不能保证向下转换,会直接返回空指针

    //new出的对象返回的是其堆上数据的地址，这里就是创建派生类对象存放在基类类型的指针变量下，记得自己开辟，自己后续要手动delete

    //new Derived(ptr_derived1); Derived* ptr_derived = ptr_derived1;
    //Derived* ptr_derived = new Derived
    //将基类指针转换为派生类指针
    Derived* ptr_derived = dynamic_cast<Derived*>(ptr_base);

    if(ptr_derived){
        ptr_derived->show();//成功转换，调用派生类方法
    }
    else{
        std::cout<<"Derived cast failed!"<<std::endl;
    }

    delete ptr_base;
    return 0;
}