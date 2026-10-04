#include <iostream>

class Student{
    public:
        Student(int age = 1,int height = 1){
            this -> age = age;
            this -> height = height;
            std::cout<<"执行Student的构造函数"<<std::endl;
        }

        ~Student(){
            std::cout<<"执行Student的析构函数"<<std::endl;
        }
        
        void print(){
            std::cout<<"age="<<age<<",height="<<height<<std::endl;
        }

        private:
            friend class StudentCaculate;

            friend void changeAge(Student* s,int age);

            int age;
            int height;
};

class StudentCaculate
//Student类的友元类，可以访问Student类的私有成员和受保护成员，通过实例化Student类来访问其私有和受保护成员
{
    public:
    void fun(){
        std::cout<<"age+height="<<student.age+student.height<<std::endl;
    }
    
    //此处会自动调用默认构造函数
    //默认值都是1
    //这是成员变量，随StudentCaculate对象而生而死
    //理清处生命周期和作用域相关
    Student student;
};

//友元函数，不属于任何成员函数
void changeAge(Student* s,int age){
    s -> age = age;
}

int main(){
    //声明Student友元类StudentCaculate对象
    StudentCaculate sc;

    //调用sc成员的fun，其中调用了Student的私有成员
    sc.fun();

    //为StudentCaculate设置一个非默认值
    //给其成员student重新赋值操作，调用其对象类的构造函数来实现
    sc.student = Student(10,120);

    sc.fun();

    return 0;
}