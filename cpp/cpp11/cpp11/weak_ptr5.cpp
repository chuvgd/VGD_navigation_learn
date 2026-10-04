#include <iostream>
#include <memory>

struct TA;
struct TB;

struct TA{
    std::shared_ptr<TB> bptr;
    ~TA(){
        std::cout<<"class TA is disstruct..."<<std::endl;
    }
};

struct TB{
    std::shared_ptr<TA> aptr;
    ~TB(){
        std::cout<<"class TB is disstruct..."<<std::endl;
    }
};

void testPtr(){
    std::shared_ptr<TA> ap(new TA);//创建TA智能指针对象ap
    std::shared_ptr<TB> bp(new TB);//创建TB智能指针对象bp

    std::cout<<"TA object use_count:"<<ap.use_count()<<std::endl;
    std::cout<<"TB object use_count:"<<bp.use_count()<<std::endl;

    ap -> bptr = bp;//将bp这个智能指针对象给ap对象里面的bptr成员，现在TB的原始内存的引用计数变成2
    bp -> aptr = ap;//和上述同理
    std::cout<<"TA object use_count:"<<ap.use_count()<<std::endl;
    std::cout<<"TB object use_count:"<<bp.use_count()<<std::endl;    
}
//核心原因：两个对象各自用shared_ptr持有对方，导致它们的引用计数永远降不到0
//两个对象里面始终有相互的智能指针对象，就是TA和TB对象里面始终有智能指针的成员——它们自己（对象里面套对方的对象），相互等待释放后析构，导致TA和TB对象一直存在堆上，直到程序完全退出
//导致内存泄漏

int main(){
    testPtr();
    return 0;
}