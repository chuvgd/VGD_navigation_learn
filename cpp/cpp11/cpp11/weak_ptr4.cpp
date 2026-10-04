#include <iostream>
#include <memory>

struct Test : public std::enable_shared_from_this<Test>
{
    std::shared_ptr<Test> getSharedPtr(){
        return std::enable_shared_from_this<Test>::shared_from_this();
    }

    ~Test(){
        std::cout<<"class Test is disstruct..."<<std::endl;
    }
};

int main(){
    std::shared_ptr<Test> sp1(new Test);//要先初始化一个对象以便weak_ptr进行获取和调用
    //std::enable_shared_from_this<Test>::shared_from_this()方法大概是：
    //std::weak_ptr<Test> ptr1 = sp1;
    //sp2 = ptr1.lock();
    std::cout<<"use_count:"<<sp1.use_count()<<std::endl;
    std::shared_ptr<Test> sp2 = sp1 -> getSharedPtr();
    std::cout<<"use_count:"<<sp1.use_count()<<std::endl;

    return 0;
}
