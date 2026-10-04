#include <iostream>
#include <string>

//创建学生数据类型 ：包括姓名，年龄，分数
struct Student
{
    //成员列表——属性
    std::string name;
    int age;
    int score;
}s3;//Student是数据类型——和int等没有区别；s3就是定义的一个变量名


int main(){
//通过学生类型创建具体学生
struct Student s1;
s1.name = "vgd";
s1.age = 18;
s1.score = 98;
std::cout<<"姓名："<<s1.name<<" 年龄："<<s1.age<<" 成绩："<<s1.score<<std::endl;

struct Student s2 = {
    "xiaoming",
    16,
    93,
};
std::cout<<"姓名："<<s2.name<<" 年龄："<<s2.age<<" 成绩："<<s2.score<<std::endl;

s3.name = "rm";
s3.age = 17;
s3.score = 96;
std::cout<<"姓名："<<s3.name<<" 年龄："<<s3.age<<" 成绩："<<s3.score<<std::endl;

return 0;
}