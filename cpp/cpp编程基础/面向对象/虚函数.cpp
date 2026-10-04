#include <iostream>

using namespace std;

class Animal{
    public: 
        virtual void sound(){
            cout<<"Animal makes a sound"<<endl;
        }
};

class Dog : public Animal{
    public:
        void sound() override{//重写虚函数
            cout<<"Dog barks"<<endl;
        }
};

int main(){
    Animal* animal = new Dog();
    animal -> sound();
    delete animal;

    return 0;
}

//在基类中可以有实现：通过虚函数在基类中提供默认实现，但子类可以选择重写
//动态绑定：在运行时根据对象的实际类型调用相应的函数版本
//可选重写：派生类可以选择性地重写虚函数，但是不是必须