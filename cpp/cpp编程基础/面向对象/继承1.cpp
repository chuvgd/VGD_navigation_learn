#include <iostream>

using namespace std;

//基类1
class Shape{
    public:
        void setWidth(int w){
            width = w;
        }
        void setHeight(int h){
            height = h;
        }
        protected:
            int width;
            int height;
};

//基类2
class PaintCost{
    public:
        int getCost(int area){
            return area*70;
        }
};

//派生类
class Rectangle : public Shape,public PaintCost{
    public:
        int getArea(){
            return (width*height);
        }
};

int main(){
    Rectangle Rect;
    int area;

    Rect.setWidth(5);
    Rect.setHeight(7);

    area = Rect.getArea();

    //输出面积
    std::cout<<"Total Area:"<<Rect.getArea()<<std::endl;
    std::cout<<"Total Area:"<<area<<std::endl;

    //输出总花费
    std::cout<<"Total paint cost:"<<Rect.getCost(area)<<std::endl;

    return 0;
}