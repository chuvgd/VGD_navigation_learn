#include <iostream>
#include <string>

class Person{
    public:
        Person(int id , std::string name){
            std::cout<<"id:"<<id<<",name:"<<name<<std::endl;
        }
};

Person func(){
    //返回类匿名对象
    return {9527,"vgd"};
}

int main(){
    Person p = func();
    return 0;
}