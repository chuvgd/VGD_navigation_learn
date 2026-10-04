#include <iostream>

using namespace std;

class Line{
    public:
        double length;
        void setLength(double len);
        double getLength(void);
};

double Line::getLength(void){
    return length;
}

void Line::setLength(double len){
    length = len;
}

int main(){
    Line line;

    //设置长度
    line.setLength(6.0);

    cout<<"Length of line :"<<line.getLength()<<endl;

    //不使用成员函数去设置长度
    //这个是成立的，因为length是公有的
    cout<<"Length of line :"<<line.length<<endl;

    return 0;
}