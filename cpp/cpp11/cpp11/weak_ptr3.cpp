#include <iostream>
#include <memory>

struct Test
{
    std::shared_ptr<Test> getSharedPtr(){
        return std::shared_ptr<Test>(this);
    }

    ~Test(){
        std::cout<<"class Test is disstruct..."<<std::endl;
    }
};

int main(){
    std::shared_ptr<Test> sp1(new Test);//只new了一次，只有一个对象，第一个this
    std::cout<<"use_count:"<<sp1.use_count()<<std::endl;
    std::shared_ptr<Test> sp2 = sp1->getSharedPtr();//调用的是sp1管理的对象的this指针去new一个新的共享指针，实际上sp2拿到的是sp1对象的指针
    //相当于sp1和sp2都是管理同一个对象的地址，但是相互不知道
    std::cout<<"use_count:"<<sp1.use_count()<<std::endl;

    return 0;
}

//此代码从头到尾只有一个Test对象，sp1和sp2指向的是同一个对象，但是各自拿着一套独立的引用计数，最后会把同一个对象delete两次

