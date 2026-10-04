#include <iostream>

//私有对象只有类自身的成员函数与被授予友元权限的实体能够操作这些内容

//实际操作中，我们一般会在私有区域定义数据，在公有区域定义相关函数，以便在类的外部也可以调用这些函数

class Box{
    public:
        double length;
        void setWidth(double wid);
        double getWidth(void);

        private:
            double width;
};

double Box::getWidth(void){
    return width;
}

void Box::setWidth(double wid){
    width = wid;
}

int main(){
    Box box;

    //私有成员不可被外部实例化访问到
    // box.width = 1.0;

    box.length = 1.0;//允许操作的行为
    box.setWidth(1.2);

    std::cout<<"Length of Box:"<<box.length<<std::endl;
    std::cout<<"Width of Box:"<<box.getWidth()<<std::endl;

    return 0;
}