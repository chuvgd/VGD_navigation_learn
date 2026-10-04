#include <iostream>

using namespace std;

class Shape{
    protected:
        int width,height;//宽度和高度

    public:
        Shape(int a = 0,int b = 0) : width(a),height(b){}

        //虚函数area,，用于计算面积
        virtual int area(){
            cout<<"Shape class area:"<<endl;
            return 0;
        }
};

class Rectangle : public Shape{
    public:
        Rectangle(int a = 0,int b = 0) : Shape(a,b){}
        //父类是有参构造，需要传入参数进行显式初始化

        int area() override{
            cout<<"Rectangle class area:"<<endl;
            return width*height;
        }
};

class Triangle : public Shape{
    public:
        Triangle(int a = 0,int b = 0) : Shape(a,b){}

        int area() override{
            cout<<"Triangle class area:"<<endl;
            return (width*height/2);
        }
};

int main(){
    Shape* shape;
    Rectangle rec(10,7);
    Triangle tri(10,5);

    shape = &rec;
    cout<<"Rectangle Area:"<<shape -> area()<<endl;

    shape = &tri;
    cout<<"Triangle Area:"<<shape -> area()<<endl;

    return 0;
}