#include <iostream>

struct Student{
    std::string name;
    int age;
    int score;
};

//值传递
void printfStudent(Student stu){
    stu.age = 100;
    std::cout<<"学生姓名："<<stu.name<<" 学生年龄："<<stu.age<<" 学生分数："<<stu.score<<std::endl;
}

//地址传递
void printfStudent01(Student* p){
    p -> age = 200;
    std::cout<<"学生姓名："<<p->name<<" 学生年龄："<<p->age<<" 学生分数："<<p->score<<std::endl;
}

int main(){
    //结构体做函数参数

    Student s;
    s.name = "rm";
    s.age = 20;
    s.score = 85;

    Student s1;
    s1.name = "vgd";
    s1.age = 18;
    s1.score = 98;

    // Student* p = &s1;

    printfStudent(s);
    std::cout<<"学生姓名："<<s.name<<" 学生年龄："<<s.age<<" 学生分数："<<s.score<<std::endl;
    std::cout<<std::endl;

    printfStudent01(&s1);
    std::cout<<"学生姓名："<<s1.name<<" 学生年龄："<<s1.age<<" 学生分数："<<s1.score<<std::endl;

    return 0;
}

//这里再次声明一点：值传递和地址传递本质上是一样的，都是会对传入的实际参数进行复制，但是复制的对象不一样，最后输出的结果不同
//值传递：复制的就是实际参数，函数运行结束值之后会自动释放掉复制的实际参数，main的实际参数仍然没有进行改变，函数中进行变化的就是那块被复制的实际参数
//地址传递：复制的是被传入的地址，实际参数的地址相同，操作复制的地址和父本没有区别，函数中变化的就是那块内存空间下的参数