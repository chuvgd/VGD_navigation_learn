#include <iostream>
#include <memory>

struct TA;
struct TB;

struct TA{
    std::weak_ptr<TB> bptr;
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

    ap -> bptr = bp;
    bp -> aptr = ap;
    std::cout<<"TA object use_count:"<<ap.use_count()<<std::endl;
    std::cout<<"TB object use_count:"<<bp.use_count()<<std::endl;    
}

//由于定义中是ap先定义，bp再定义，离开函数作用域的时候bp先析构，ap再析构，bp析构——由于std::weak_ptr<TB> bptr是weak_ptr，所以TB对象的智能指针的引用计数只有1,bp析构变成0,TB对象析构
//TB析构的时候其成员对象也析构，TA的引用计数变成1,ap析构时候引用计数变成0,TA对象析构


int main(){
    testPtr();
    return 0;
}