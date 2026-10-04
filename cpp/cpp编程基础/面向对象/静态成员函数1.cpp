#include <iostream>

using namespace std;


//静态成员只有一个副本
class Box{
    public:
        static int objectCount;
        //构造函数定义
        Box(double l = 2.0,double b = 2.0,double h = 2.0):length(l),breadth(b),height(h)
        {
            cout<<"Constructor called."<<endl;
            objectCount++;
        }
        double Volume(){
            return length*breadth*height;
        }
    
    private:
        double length; //长度
        double breadth; //宽度
        double height; //高度
};

//初始化Box的静态成员
int Box::objectCount = 0;

int main(){
    Box box1(3.3,1.2,1.5);//声明box1
    cout<<"vol of box1:"<<box1.Volume()<<endl;
    Box box2(8.5,6.0,2.0);//声明box2
    cout<<"vol of box2:"<<box2.Volume()<<endl;

    cout<<"Total objects:"<<box1.objectCount<<endl;
    cout<<"Total objects:"<<box1.objectCount<<endl;
    cout<<"Total objects:"<<Box::objectCount<<endl;

    return 0;
}