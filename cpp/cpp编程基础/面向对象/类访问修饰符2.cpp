#include <iostream>

//protected主要是为了继承，如果没有继承——和private一样；如果有继承，子类可以访问到父类的protected成员，但是无法访问private
class Box{
    protected:
        double width;
};

class SmallBox:Box//SmallBox是派生类
{
    public:
        void setSmallWidth(double wid);
        double getSmallWidth(void);
};

//派生类成员函数
double SmallBox::getSmallWidth(void){
    return width;
}

void SmallBox::setSmallWidth(double wid){
    width = wid;
}

int main(){
    SmallBox box1;

    //使用成员函数设置宽度
    box1.setSmallWidth(5.5);
    std::cout<<"Width of Box:"<<box1.getSmallWidth()<<std::endl;

    return 0;
}

