#include <iostream>
#include <memory>

int main(){
    std::shared_ptr<int> sp(new int);

    std::weak_ptr<int> wp1;//空对象
    std::weak_ptr<int> wp2(wp1);//还是空对象
    std::weak_ptr<int> wp3(sp);//通过共享指针构造了一个可用的对象
    std::weak_ptr<int> wp4;
    wp4 = sp;//隐式类型转换，构造可用的weak_ptr对象
    std::weak_ptr<int> wp5;
    wp5 = wp3;//可用对象


    std::cout<<"use_count:"<<std::endl;
    std::cout<<"wp1:"<<wp1.use_count()<<std::endl;
    std::cout<<"wp1:"<<wp2.use_count()<<std::endl;
    std::cout<<"wp1:"<<wp3.use_count()<<std::endl;
    std::cout<<"wp1:"<<wp4.use_count()<<std::endl;
    std::cout<<"wp1:"<<wp5.use_count()<<std::endl;
    //这里wp3,wp4,wp5监测的资源是同一个，它的引用计数并没有发生任何变换，weak_ptr只是监测资源，并不管理
    
    return 0;
}