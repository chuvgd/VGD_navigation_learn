#include <iostream>

using namespace std;

class Shape{
    public:
        void setWidth(int w){
            width = w;
        }
        void setHight(int h){
            height = h;
        }

        protected:
            int width;
            int height;
};

class Rectangle : public Shape{
    public:
        int getArea(){
            return (width*height);
        }
};

int main(){
    Rectangle Rect;

    Rect.setWidth(5);//成员函数继承而来
    Rect.setHight(7);

    //输出对象面积
    std::cout<<"Total area:"<<Rect.getArea()<<std::endl;

    return 0;
}