#include <iostream>
using namespace std;

struct Person{
    const char* name;
    int age;
};

template<typename T>
constexpr T display(T t){
    return t;
}

int main(){
    struct Person p{"vgd",11};

    //普通函数
    struct Person ret = display(p);
    //p为变量，constexpr无效
    std::cout<<"name:"<<ret.name<<",age:"<<ret.age<<std::endl;

    //常量表达式函数
    constexpr int ret1 = display(250);
    //参数是常量，constexpr有效
    std::cout<<ret1<<std::endl;

    constexpr struct Person p1{"vgd",11};
    //参数是常量
    constexpr struct Person p2 = display(p1);
    std::cout<<"name:"<<p2.name<<",age:"<<p2.age<<std::endl;

    return 0;
}