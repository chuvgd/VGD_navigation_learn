#include <iostream>
#include <memory>

int main(){
    std::shared_ptr<int> shared(new int(10));
    std::weak_ptr<int> weak(shared);
    std::cout<<"1.weak "<<(weak.expired()?"is":"is not")<<" expired"<<std::endl;

    //shared.reset();
    weak.reset();
    //weak.reset()变成了空对象，不再监测任何资源
    std::cout<<"2.weak "<<(weak.expired()?"is":"is not")<<" expired"<<std::endl;
    //weak_ptr监管的是shared_ptr的资源，当shared释放之后，weal.expired()函数的结果返回true，表示监测的资源已经不存在了

    return 0;
}