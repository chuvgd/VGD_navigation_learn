#include <iostream>

using namespace std;

class Student{
    private:
        string name;
        int age;
    
    public:
        //构造函数
        Student(string studentName,int studentAge){
            name = studentName;
            age = studentAge;
        }

        //访问器函数(getter)
        string getName(){
            return name;
        }

        int getAge(){
            return age;
        }

        //函数修改器(setter)
        void setName(string studentName){
            name = studentName;
        }

        void setAge(int studentAge){
            if(studentAge > 0){
                age = studentAge;
            }else {
                cout<<"Invalid age!"<<endl;
            }
        }

        void printInfo(){
            cout<<"Name:"<<name<<",Age:"<<age<<endl;
        }
};

int main(){
    //创建一个Student对象
    Student student("Alice",20);

    //访问和修改数据
    student.printInfo();

    student.setName("Bob");
    student.setAge(22);

    student.printInfo();

    return 0;
}