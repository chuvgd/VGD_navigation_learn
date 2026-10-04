#include <iostream>

using namespace std;

class Box{
    public:
        static int objectCount; //= 1;静态成员数据的初始化不能放在类内部
        //构造函数定义
        Box(double length,double breadth,double height){
            this -> breadth = breadth;
            this -> length = length;
            this -> height = height;
            objectCount++;
        }
        double vol(){
            return breadth*length*height;
        }
        static int returnobj(){
            return objectCount;
        }

    private:
        double length;
        double breadth;
        double height;
};

int Box::objectCount = 0;//初始化必须在类外用作用域解析符进行赋值操作

int main(){
    cout<<"counts of obj:"<<Box::returnobj()<<endl;

    Box box1(1.2,2.8,5.0);
    cout<<"vol of box1:"<<box1.vol()<<endl;
    Box box2(2.0,4.0,5.0);
    cout<<"vol of box2:"<<box2.vol()<<endl;

    cout<<"counts of obj:"<<Box::returnobj()<<endl;

    return 0;
}