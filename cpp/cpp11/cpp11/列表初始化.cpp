#include <iostream>

class Test{
    public:
        Test(int){};
    private:
        Test(const Test&);
};

int main(){
    Test t1(520);
    //如果g++是-std=c++11就会出现编译错误
    //拷贝构造函数是私有的，如果是公有的，520会被隐式转换成Test(int)构造一个匿名对象，然后匿名对象浅拷贝得到t2
    Test t2 = 520;
    //t3和t4都是cpp11初始化的方式（=有无没有影响）
    Test t3 = {520};
    Test t4{520};

    return 0;
}