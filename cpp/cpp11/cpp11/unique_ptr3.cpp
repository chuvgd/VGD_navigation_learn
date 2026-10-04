#include <iostream>
#include <memory>

// std::shared_ptr<int> ptr1(new int(10),[](int* p){delete p;}); ok
// std::unique_ptr<int> ptr1(new int(10),[](int* p){delete p;}); error

int main(){
    using func_ptr = void(*)(int*);
    //func_ptr的类型和lmabda类型一致,这是因为lambda函数没有捕获外部变量，可以直接转换为函数指针，一旦捕获了就无法转换了
    std::unique_ptr<int,func_ptr> ptr1(new int(10),[](int* p){delete p;});

    return 0;
}