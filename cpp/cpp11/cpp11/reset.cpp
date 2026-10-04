#include <iostream>
#include <string>
#include <memory>

// using namespace std;

int main(){
    //使用智能指针管理一块int型的堆内存，内部引用计数为1
    std::shared_ptr<int> ptr1 = std::make_shared<int>(520);
    std::shared_ptr<int> ptr2 = ptr1;
    std::shared_ptr<int> ptr3 = ptr1;
    std::shared_ptr<int> ptr4 = ptr1;
    //查看当前多少个智能指针同时管理这块内存——共享智能指针的成员函数use_count

    std::cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << std::endl;
    std::cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << std::endl;

    ptr4.reset();//放弃对当前内存的管理
    std::cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << std::endl;
    std::cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << std::endl;

    std::shared_ptr<int> ptr5;
    ptr5.reset(new int(250));//先释放旧的内存再去接管一个新的堆内存
    std::cout << "ptr5管理的内存引用计数: " << ptr5.use_count() << std::endl;
   
    return 0;
}