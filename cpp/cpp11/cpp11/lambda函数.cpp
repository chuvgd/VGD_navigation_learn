#include <iostream>
#include <functional>

using namespace std;

class Test{
    public:
        void output(int x,int y){
            auto x1 = []{
                //return m_number;
            }; //error:没有捕获外部变量，不能使用类成员m_number
            auto x2 = [=]{
                return m_number;
            };//ok,以值拷贝的方式去捕获所有的变量
            auto x3 = [&]{
                return m_number;
            }; //ok,以引用的方式捕获所有的外部变量
            auto x4 = [this]{
                return m_number;
            }; //ok，捕获this指针,可以访问对象内部成员
            auto x5 = [this]{
                // return m_number + x + y;
                //注意这里：x和y是局部变量，不是类的成员，x和y是output这个成员函数的形式参数，是栈上分配的局部变量
            };//error,捕获this指针，可访问类内部成员，没有捕获到变量x和y（x和y这个变量是外部实际参数传入）
            auto x6 = [this,x,y]{
                return m_number + x + y;
            };//ok,捕获列表同时捕获了this指针和x，y变量，既可以访问类内部成员，又可以访问x和y的变量
            auto x7 = [this]{
                return m_number++;
            };//捕获了this指针，并且可以修改对象内部变量的值
        }
        //[=]——按值捕获外部作用域所有的变量，但是拷贝的副本在匿名函数体内是可读的
        //[&]——按引用捕获外部作用所有的变量，可以修改变量的内容
        //[&]和[=]是默认也会捕获类的this指针

    private:
        int m_number = 100;
};

int main(){
    Test t;
    t.output(10,20);
    
    return 0;
}