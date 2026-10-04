#include <iostream>
#include <string>

class Base{
    public:
        Base(int i):m_i(i){};
        Base(int i , double j):m_i(i),m_j(j){};
        Base(int i , double j , std::string k):m_i(i),m_j(j),m_k(k){};
       
        int m_i;
        double m_j;
        std::string m_k;
};

class Child : public Base{
    public:
        using Base::Base;
        //就是用父类构造函数去初始化子类对象
};

int main(){
    Child vgd(520,13.14,"I love you");
    std::cout<<"int:"<<vgd.m_i<<",double:"<<vgd.m_j<<",string:"<<vgd.m_k<<std::endl;

    Child vgd1(520,13.14);
    std::cout<<"int:"<<vgd1.m_i<<",double:"<<vgd1.m_j<<std::endl;

    return 0;
}