#include <iostream>
#include <exception>
using namespace std;
 
struct MyException : public std::exception
{
  const char* what() const throw()//const表示成员函数不能修改其成员变量相关状态，可被const对象调用
  //throw()承诺函数不抛出异常，只是return一个字符串，不是throw
  {
    return "C++ Exception";
  }
};
//struct和class本质是一样的，只是默认成员权限和默认继承方式
//重写函数——函数签名需要保持和虚函数一样：函数签名是指的是函数名称和函数参数（参数类型和参数顺序）
 
int main()
{
  try
  {
    throw MyException();//这是抛出异常
    //()是构造调用，不是函数声明，用默认构造函数造一个MyException对象
    //throw是把临时对象抛出去
  }
  catch(MyException& e)//捕获异常
  //e就是一个引用，绑定到被抛出的那个异常对象上（就是临时对象的别名），其实e.what()就是操作那个异常对象的本身，继承而来exception类并对what()函数进行重写（多态）
  {
    std::cout << "MyException caught" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    //其他的错误
  }
}