#include <iostream>

class Point{
    int x,y;
    public:
        Point(int x,int y):x(x),y(y)//初始化列表
        {};
        //const成员函数
        int getX() const{
            return x;
        }

        int getY() const{
            return y;
        }//非const成员函数
        void setX(int val){
            x = val;
        }
};

int main(){
    const Point p(1,2);
    std::cout<<p.getX()<<","<<p.getY()<<std::endl;//合法
    //p.setX(3);//错误！const对象不能调用非const成员函数

    Point p2(3,4);
    p2.setX(5);//合法
    std::cout<<p2.getX()<<std::endl;

    return 0;
}