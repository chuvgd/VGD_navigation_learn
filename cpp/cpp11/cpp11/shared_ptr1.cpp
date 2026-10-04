#include <iostream>
#include <memory>

int main(){
    //使用智能指针去管理一块int类型的堆内存，引用计数+1
    std::shared_ptr<int> ptr1(new int(520));
    std::cout<<"ptr1管理的内存引用计数:"<<ptr1.use_count()<<std::endl;

    //调用拷贝构造函数,引用计数+1
    std::shared_ptr<int> ptr2(ptr1);
    std::cout<<"ptr2管理的内存引用计数:"<<ptr2.use_count()<<std::endl;

    std::shared_ptr<int> ptr3 = ptr1;
    std::cout<<"ptr3管理的内存引用计数:"<<ptr3.use_count()<<std::endl;

    //调用移动构造函数
    //std::move直接转移内存的所有权，就是ptr1成为右值传入移动构造函数进行同类对象初始化
    std::shared_ptr<int> ptr4(std::move(ptr1));
    std::cout<<"ptr4管理的内存引用计数:"<<ptr4.use_count()<<std::endl;

    std::shared_ptr<int> ptr5 = std::move(ptr2);
    std::cout<<"ptr5管理的内存引用计数:"<<ptr5.use_count()<<std::endl;

    return 0;
}