#include <iostream>
#include <functional>

class Test{
    public:
        void output(int x , int y){
            std::cout<<"x:"<<x<<",y:"<<y<<std::endl;
        }

        int m_number = 100;
};

int main(){
    Test t;
    //绑定类成员函数
    std::function<void(int,int)> f1 = std::bind(&Test::output,&t,std::placeholders::_1,std::placeholders::_2);
    //绑定类成员变量
    std::function<int&(void)> f2 = std::bind(&Test::m_number,&t);

    //调用
    f1(520,1314);
    f2() = 2333;
    std::cout<<"t.number:"<<t.m_number<<std::endl;

    return 0;
}