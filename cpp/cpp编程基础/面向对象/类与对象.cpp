#include <iostream>

class Box{
    public:
    double length;
    double breath;
    double height;
    //成员函数声明
    double get(void);
    void set(double len,double bre,double hei);
};

double Box::get(void){
    return length*breath*height;
}

void Box::set(double len,double bre,double hei){
    length = len;
    breath = bre;
    height = hei;
}

int main(){
    Box box1;
    // Box box2;
    Box box3;
    double vol = 0.0;

    box1.height = 5.0;
    box1.breath = 6.0;
    box1.length = 7.0;

    box3.set(1.0,20.0,7.0);

    vol = box1.height*box1.breath*box1.length;
    std::cout<<"box1的体积"<<vol<<std::endl;

    vol = box3.get();
    std::cout<<"box3的体积"<<vol<<std::endl;
}