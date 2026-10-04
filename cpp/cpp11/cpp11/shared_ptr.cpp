#include <iostream>
#include <memory>

using namespace std;

int main(){
    std::shared_ptr<int> ptr1(new int(520));
    std::cout<<"ptr1管理的内存引用计数:"<<ptr1.use_count()<<std::endl;

    std::shared_ptr<char> ptr2(new char[12]);
    std::cout<<"ptr2管理的内存引用计数:"<<ptr2.use_count()<<std::endl;
   
    std::shared_ptr<int> ptr3;
    std::cout<<"ptr3管理的内存引用计数:"<<ptr3.use_count()<<std::endl;

    std::shared_ptr<int> ptr4(nullptr);
    std::cout<<"ptr4管理的内存引用计数:"<<ptr4.use_count()<<std::endl;

    return 0;
}