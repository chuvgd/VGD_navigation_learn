//表达式是一个左值，或者被括号()包围，使用decltype推导出的是表达式的引用
#include <iostream>
#include <vector>
using namespace std;

class Test{
    public:
        int num;
        Test(){};
};

int main(){
    const Test obj;
    //带有括号的表达式
    decltype(obj.num) a = 0;//为类的成员表达式，推导出int
    decltype((obj.num)) b = a;//带有括号,推导出的类型为const int&
    //加法表达式
    int n = 0,m = 0;
    decltype(n+m) c = 0;//得到的右值
    decltype(n = n + m) d = n;//得到的是左值n
    
    return 0;
}