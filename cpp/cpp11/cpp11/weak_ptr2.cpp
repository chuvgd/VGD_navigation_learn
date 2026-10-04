#include <iostream>
#include <memory>

int main(){
    std::shared_ptr<int> sp1,sp2;
    std::weak_ptr<int> wp;

    sp1 = std::make_shared<int>(520);
    wp = sp1;
    sp2 = wp.lock();
    //通过lock()方法得道一个用于管理weak_ptr对象所监测的资源的共享智能指针对象，使用这个对象初始化sp2，原始内存现在的引用计数为2
    std::cout<<"use_count:"<<wp.use_count()<<std::endl;

    sp1.reset();
    //sp1被释放，原始内存的引用计数减1
    std::cout<<"use_count:"<<wp.use_count()<<std::endl;

    sp1 = wp.lock();
    //wp现在监测的原始内存只有sp2进行管理，现在把原始内存再次给sp1,引用计数+1
    //共享智能指针对象sp1和sp2管理的是同一块内存
    std::cout<<"use_count:"<<wp.use_count()<<std::endl;

    std::cout<<"*sp1 = "<<*sp1<<std::endl;
    std::cout<<"*sp2 = "<<*sp2<<std::endl;

    return 0;
}

