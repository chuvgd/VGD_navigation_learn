#include <iostream>

using namespace std;

//只有通过基类的指针或引用调用虚函数时，才会发生多态
class Animal{
    public:
        //在成员函数参数列表后面加const，表示该函数不会修改对象状态
        virtual void sound() const {
            cout<<"Animals makes a sound"<<endl;
        }
        
        //纯虚析构函数确保子类对象被正确析构
        virtual ~Animal(){
            cout<<"Animals destroyed"<<endl;
        }
};

class Dog : public Animal{
    public:
        //override关键字对虚函数进行重写
        void sound() const override{
            cout<<"Dogs barks"<<endl;
        }

        ~Dog(){
            cout<<"Dog destroyed"<<endl;
        }
};

class Cat : public Animal{
    public:
        void sound() const override{
            cout<<"Cat meows"<<endl;
        }

        ~Cat(){
            cout<<"Cat destroyed"<<endl;
        }
};

int main(){
    //基类指针
    Animal* animalPtr;

    //创建Dog对象，并指向Animal指针
    animalPtr = new Dog();
    //调用Dog的sound方法
    animalPtr -> sound();
    delete animalPtr;

    animalPtr = new Cat();
    animalPtr -> sound();
    delete animalPtr;//释放内存，调用Cat和Animal的析构函数

    return 0;
}

//对类类型（有默认构造函数）:new Dog() = new Dog;
//对内置类型(int,char等):()会触发零初始化，不加则是未定义值
//new type(value)=>表示的是要求一个类型表达式

//~Animal()为虚构函数，确保在释放基类指针指向的派生类对象时能够正确调用派生类的析构函数，防止内存泄漏