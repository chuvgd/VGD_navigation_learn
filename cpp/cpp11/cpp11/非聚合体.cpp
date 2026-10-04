#include <iostream>
#include <string>

struct T1
{
    /* data */
    int x;
    int y;
    //自定义构造函数
    T1(int a , int b , int c):x(a),y(b),z(c){};
    virtual void print(){
        std::cout<<"x:"<<x<<",y:"<<y<<",z:"<<z<<std::endl;
    }


private:
    int z;
};

int main(){
    //基于构造函数使用初始化列表初始化类成员
    T1 t{520,13,1314};
    t.print();

    return 0;
}
