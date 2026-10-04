//表达式是普通变量或者普通表达式或者类表达式，在这种情况下，使用decltype推导出的类型和表达式的类型是一致的
#include <iostream>
#include <string>

using namespace std;

class Test{
    public:
        string text;
        static const int value = 100;
};

int main(){
    int x = 99;
    const int& y = x;
    decltype(x) a = x;
    decltype(y) b = x;
    decltype(Test::value) c = 0;


    Test t;
    decltype(t.text) d = "hello world";

    return 0;
}