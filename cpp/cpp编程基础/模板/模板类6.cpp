//类模板与静态成员
#include <iostream>

template <class T>
class A
{
    private:
        static int count;//静态成员——属于所有对象
    public:
        A(){
            count++;
        }
        ~A(){
            count--;
        }
        A(A&){
            count++;
        }

        static void PrintCount(){
            std::cout<< count << std::endl;
        }//静态函数
};

//初始化静态成员时，前面需要加template<>
template<> int A<int>::count = 0;
template<> int A<double>::count = 0;

int main(){
    A<int> ia;
    A<double> da;//da和ia不是相同的(模板)类，因而输出相关的静态成员是根据相同类下的不同对象判定的
    ia.PrintCount();
    da.PrintCount();

    return 0;
}