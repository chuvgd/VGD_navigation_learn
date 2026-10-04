#include <iostream>

struct Test
{
    int id;
    int num;
};

int main(){
    constexpr Test t{1,2};
    constexpr int id = t.id;
    constexpr int num = t.num;
    //error,不能修改常量
    // t.num+=100;
    std::cout<<"id:"<<id<<",num:"<<num<<std::endl;

    return 0;
}
