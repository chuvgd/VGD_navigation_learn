#include <iostream>

struct Student{
    std::string name;
    int age;
    int score;
};

//将函数中的形式参数改为指针，可以减少内存空间的开销
void printfStudent(const Student* stu){
    //加入const之后，一旦有修改的操作就会报错，可以防止误操作，这个同样适用于其他基本数据类型，const——只读（常量）
    //stu -> age = 200;
    std::cout<<"学生姓名:"<<stu->name<<" 学生年龄:"<<stu->age<<" 学生分数:"<<stu->score<<std::endl;
}

int main(){
    Student s = {"vgd",19,100};
    printfStudent(&s); 
}