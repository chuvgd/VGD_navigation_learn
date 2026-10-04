#include <iostream>
#include <string>

using namespace std;

struct MyException
{
    MyException(string s) :msg(s) {}
    string msg;
};

double divisionMethod(int a, int b) throw(MyException, int)
{
    if (b == 0)
    {
        throw 100;
        throw MyException("division by zero!!!");
        // throw 100;
        //抛出异常
    }
    return a / b;
}

int main()
{
    try
    {	
        double v = divisionMethod(100, 0);
        cout << "value: " << v << endl;
    }
    catch (int e)//e就是抛出异常类型的实例化，即throw异常之后将具体的异常赋值给e这个栈上变量
    {
        cout << "catch except: "  << e << endl;
    }//捕获到int类型异常，但是没有具体抛出实例给int e
    catch (MyException e)
    {
        cout << "catch except: " << e.msg << endl;
    }//捕获到struct MyException下的msg："division by zero!!!"
    return 0;
}