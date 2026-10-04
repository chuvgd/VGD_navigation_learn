#include <iostream>
struct student{
    std::string name;
    int age;
    int score;
};

struct teacher
{
    int id;
    std::string name;
    int age;
    struct student stu;
};

int main(){
    teacher t;
    t.id = 10000;
    t.name = "老王";
    t.age = 50;
    t.stu.age = 20;
    t.stu.name = "vgd";
    t.stu.score = 60;

    std::cout<<"老师姓名："<<t.name<<" 老师编号:"<<t.id<<" 老师年龄："<<t.age<<std::endl;
    std::cout<<"学生姓名："<<t.stu.name<<" 学生年龄："<<t.stu.age<<std::endl;

    return 0;
}
