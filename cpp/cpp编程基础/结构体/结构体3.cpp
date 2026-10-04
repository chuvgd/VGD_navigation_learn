#include <iostream>

struct Student{
    std::string name;
    int age;
    int score;
};

int main(){
    struct Student s = {"vgd",15,100};

    struct Student* p = &s;

    std::cout<<"姓名："<<p -> name<<" 年龄："<<p -> age<<" 分数:"<<p ->score<<std::endl;

    return 0;
}

