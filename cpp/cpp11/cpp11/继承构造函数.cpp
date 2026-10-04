#include <iostream>
#include <string>
using namespace std;

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
        Child(int i):Base(i){};
        //父类有参构造函数必须用初始化列表先对父类进行构造再去子类构造
        //这里就是子类构造函数接收参数然后先对父类进行构造函数（传入父类）
        Child(int i , double j):Base(i,j){};
        Child(int i , double j , std::string k):Base(i,j,k){};
};

int main(){
    Child vgd(520,13.14,"I love you");
    std::cout<<"int:"<<vgd.m_i<<",double:"<<vgd.m_j<<",string:"<<vgd.m_k<<std::endl;

    return 0;
}