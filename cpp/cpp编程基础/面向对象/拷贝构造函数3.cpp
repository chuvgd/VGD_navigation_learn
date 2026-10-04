#include <iostream>

class Time{
    public:
        Time(){
            _hour = 1;
            _minute = 1;
            _second = 1;
        }
        Time(const Time &t){
            _hour = t._hour;
            _minute = t._minute;
            _second = t._second;
            std::cout<<"Time::Time(const Time &)"<<std::endl;
        }

    private:
        int _hour;
        int _minute;
        int _second;
};

class Date{
    private:
        //基本类型（内置类型）
        int _year = 1970;
        int _month = 1;
        int _day = 1;
        //自定义类型
        Time _t;
    public:
        // Date(){};
        // Date(const Date &date){};
};

int main(){
    Date d1;//这个是直接调用Date()，其成员是初始化得到_year/_month/_day这三个内置类型，自定义类型_t会调用Time()这个构造函数，给Time类型的_t的成员初始化（也是_year/_month/_day），但是是_t的成员（均为1）

    //用已经存在的d1拷贝构造d2,此处会调用Date类的拷贝构造函数
    //但Date类并没有显式定义拷贝构造函数，则编译器会给Date类生成一个默认拷贝构造函数
    //默认拷贝函数会按内存存储逐成员拷贝——拷贝方式就是见下“注意”
    Date d2(d1);
    //这个是d2拷贝d1,由于没有拷贝构造函数的实现，编译器会给出一个默认拷贝构造函数，这个拷贝构造函数会进行内存逐字节拷贝，首先是拷贝d1自己的成员，后续是对_t进行拷贝，调用了Time(const Time &)进行拷贝构造，从d1拷贝，均是1
    return 0;
}

//注意：在编译器生成的默认拷贝构造函数中，内置类型是按照字节方式直接拷贝的，而自定义类型是调用其拷贝构造函数完成拷贝的
//自定义类型调用拷贝构造函数——主要是看有没有被放到拷贝构造的初始化列表（或者编译器自动生成的逐成员拷贝），有就调用拷贝构造，没有就用默认构造