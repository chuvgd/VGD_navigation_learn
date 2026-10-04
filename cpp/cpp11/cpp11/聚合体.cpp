#include <iostream>
#include <string>

struct T1
{
    /* data */
    int x;
    int y;
}a = {123,321};

struct T2
{
    /* data */
    int x;
    int y;
    T2(int,int):x(10),y(20){}
}b = {123,321};

int main(){
    std::cout<<"a.x:"<<a.x<<" a.y:"<<a.y<<std::endl;
    std::cout<<"b.x:"<<b.x<<" b.y:"<<b.y<<std::endl;
   
    return 0;
}