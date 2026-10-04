#include <iostream>
#include <string>
#include <vector>
using namespace std;

using func_ptr = void(*)(int, string);
struct Test
{
    static void print(int a, string b)
    {
        cout << "name: " << b << ", age: " << a << endl;
    }

    // 将类对象转换为函数指针
    operator func_ptr()
    {
        return print;
    }
};

int main(void)
{
    Test t;
    // 对象转换为函数指针, 并调用
    t(19, "Monkey D. Luffy");

    return 0;
}