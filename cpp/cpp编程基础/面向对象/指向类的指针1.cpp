#include <iostream>

class Myclass{
    public:
        int data;

        void display(){
            std::cout<<"Data:"<<data<<std::endl;
        }
};

int main(){
    Myclass obj;
    obj.data = 42;

    //声明和初始化指向类的指针
    Myclass* ptr = &obj;

    std::cout<<"Data via pointer:"<<ptr ->data<<std::endl;

    //通过指针调用成员函数
    ptr -> display();

    return 0;
}