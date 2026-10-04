#include <iostream>

using namespace std;

class Box{
    public:

        double getVolume(void){
            return length * breadth * height;
        }

        void setLength(double len){
            length = len;
        }

        void setBreadth(double bre){
            breadth = bre;
        }

        void setHeight(double hei){
            height  = hei;
        }

        //重载+运算符，把两个Box对象相加
        //这里Box就是函数类型，operator +就是函数名,(const Box& b)就是函数形式参数列表
        Box operator + (const Box& b)
        //实际上是Box operator + (const Box* const this,const Box& b)
        {
            Box box;
            box.length = this -> length + b.length;
            box.breadth = this -> breadth + b.breadth;
            box.height = this -> length + b.height;
            return box;
        }

    private:
        double length;
        double breadth;
        double height;
};

int main(){
    Box box1;
    Box box2;
    Box box3;
    double vol = 0.0;

    box1.setLength(7.0);
    box1.setBreadth(5.0);
    box1.setHeight(2.0);

    box2.setLength(7.0);
    box2.setBreadth(2.0);
    box2.setHeight(2.0);


    vol = box1.getVolume();
    cout<<"vol of box1:"<<vol<<endl;

    vol = box2.getVolume();
    cout<<"vol of box2:"<<vol<<endl; 

    box3 = box1 + box2;
    //等价于box1.operator+(box2) == box1 + box2
    //这个是运算符的固定规则，如果作为成员函数，运算符左侧对象被隐式绑定到this指针上，也就是去调用box1的成员函数operator +,传入box2，然后函数最后返回局部变量的box3(box3相关成员等)
    //然后把返回的局部变量值给box3

    vol = box3.getVolume();
    cout<<"vol of box3:"<<vol<<endl; 

    return 0;
}

//其实就是函数重载——函数名相同，都是operator +，函数的形式参数列表不同，构成函数重载
//但是函数类型（函数返回值）不作为函数重载的判断，函数类型不同没有关系