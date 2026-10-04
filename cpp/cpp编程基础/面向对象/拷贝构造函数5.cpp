#include <iostream>

class Date{
    public:
        Date(int year,int minute,int day){
            std::cout<<"Date(int,int,int):"<<this<<std::endl;
        }
        Date(const Date& d){
            std::cout<<"Date(const Date& d):"<<this<<std::endl;
        }
        ~Date(){
            std::cout<<"~Date():"<<this<<std::endl;
        }
    //     // Date Test(Date d){
    //     // Date temp(d);
    //     // return temp;
    // }

    

    private:
        int _year;
        int _month;
        int _day;
};

Date Test(Date d){
        //Date d = d1;
        Date temp(d);
        return temp;
}

int main(){
    Date d1(2022,1,13);
    Test(d1);

    return 0;
}

//一般没有资源管理（堆上数据）就不用写拷贝构造函数（默认构造函数浅拷贝即可），如果有相关资源管理就需要显式写出析构函数和拷贝构造函数进行深拷贝


