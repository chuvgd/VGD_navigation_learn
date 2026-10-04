//模板函数作为类的友元

#include <iostream>
//普通类
class A{
    private:
        int v;
    public:
        A(int n) : v(n){};

        template <class T>
        friend void Print(const T& p);//模板函数
};

//模板函数
template <class T>
void Print(const T& p){
    std::cout<< p.v<<std::endl;
}

int main(){
    A a(4);
    Print(a);
    
    return 0;
}