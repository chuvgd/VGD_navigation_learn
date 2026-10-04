#include <iostream>

//定义一个加法器类
class Adder{
    public:
        //构造函数，初始化加数
        Adder(int a) : value(a){}

        //重载函数调用操作符
        int operator()(int b) const{
            return value + b;
        }

    private:
        int value;
};

int main(){
    Adder addFive(5);
    Adder addTen(10);

    std::cout<<"5 + 3 = "<<addFive(3)<<std::endl;
    std::cout<<"10 + 7 ="<<addTen(7)<<std::endl;

    return 0;
}