#include <iostream>

using namespace std;

class Shape{
    public:
        virtual int area() = 0;//纯虚函数，强制子类实现此方法
};

class Rectangle : public Shape{
    private:
        int width,height;
    public:
        Rectangle(int w,int h) : width(w),height(h){}

        int area() override{
            return width*height;
        }
};

int main(){
    Shape* Shape = new Rectangle(10,5);
    cout<<"Rectangle Area:"<<Shape -> area()<<endl;
    delete Shape;

    return 0;
}