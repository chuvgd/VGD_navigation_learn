#include <iostream>

using namespace std;

class Line{
    public:
        Line();//构造函数的声明
        void setLength(double len);
        double getLength() const;
        //在成员函数后面加const表示的是const成员函数，表示该函数不会修改类的非静态数据成员——主要是提升代码安全性和可读性，尤其是在处理常量对象时作用显著
};
