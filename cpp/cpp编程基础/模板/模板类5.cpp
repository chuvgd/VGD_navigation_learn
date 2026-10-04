//类模板作为类模板的友元
#include <iostream>

//类模板
template <class T>
class B{
    private:
        T v;
    public:
        B(T n) : v(n){};

        template <class T2>
        friend class A; //友元类模板
};

//类模板
template <class T>
class A{
    public:
        void Func(){
            B<int> o(10);//实例化B模板类
            std::cout<<o.v<<std::endl;
        }
};

int main(){
    A<double> a;
    a.Func();

    return 0;
}