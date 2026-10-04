#include <iostream>

struct Person
{
    //初始化列表赋成员值
    constexpr Person(const char* p,int age):name(p),age(age){

    };
    const char* name;
    int age;
};

int main(){
    // constexpr Person p1 = Person("vgd",19);
    constexpr Person p1("vgd",19);

    std::cout<<"name:"<<p1.name<<",age:"<<p1.age<<std::endl;
    return 0;
}
