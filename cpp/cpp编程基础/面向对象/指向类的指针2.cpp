//动态分配内存
//指向类的指针还可以用于动态分配内存，创建类的对象

#include <iostream>

class Myclass{
    public:
        int data;

        void display(){
            std::cout<<"Data:"<<data<<std::endl;
        }
};

int main(){
    //动态分配内存创建类对象(后续引入智能指针)
    //new关键字语法
    //不初始化：Type* ptr = new Type;
    //赋初值初始化：Type* ptr = new Type(value);
    //eg. int* p1 = new int;
    //eg. int* p2 = new int(10);
    //分配一维数组：Type* ptr = new Type[size];
    //释放内存语法：1.释放单一对象 delete ptr;
    //            2.释放数组  delete[] ptr;
    Myclass* ptr = new Myclass;
    ptr -> data = 42;

    //通过指针调用成员函数
    ptr -> display();

    //释放动态分配的内存
    delete ptr;

    return 0;
}