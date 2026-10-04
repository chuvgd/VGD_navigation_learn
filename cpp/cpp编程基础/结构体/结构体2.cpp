#include <iostream>

struct Student{
        std::string name;
        int age;
        int score;
    };

int main(){
     Student studentArr[3] = {
        {"rm",11,98},
        {"chd",17,97},
        {"vgd",18,98},
     };

     studentArr[2].name = "chu";
     studentArr[2].age = 20;
     studentArr[2].score = 80;

     for(int i = 0 ; i < 3; i++){
        std::cout<<"姓名："<<studentArr[i].name<<" 年龄："<<studentArr[i].age<<" 分数："<<studentArr[i].score<<std::endl;
     }

     return 0;
}