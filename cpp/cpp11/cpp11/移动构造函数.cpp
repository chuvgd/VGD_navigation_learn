#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_NEW_MEM (64*1000*1000)

class CDate{
public:
    CDate(int year , int mon , int day);
    CDate(const CDate& date);//拷贝构造函数
    CDate(CDate&& date) noexcept;//移动构造函数
    ~CDate();

    CDate operator+(int day);

    void show(){
        cout<<"Date:"<<m_year<<"."<<m_mon<<"."<<m_day<<",this = "<<this<<endl;
    }

private:
    int m_year;
    int m_mon;
    int m_day;
    char* str;  
};

CDate::CDate(int year , int mon , int day):m_year(year),m_mon(mon),m_day(day){
    str = new char[MAX_NEW_MEM];
    sprintf(str , "%4d.%02d.%02d",year,mon,day);
    //sprintf是发送格式化输出到str所指向的字符串
    //str这个是指向一个字符数组的指针，该数组存储了c字符串
    //int sprintf(char* str , const char* format,...)
    //format字符串，包含了要被写入到字符串str文本,主要是按要求格式化
    cout<<"Calling Constructor"<<",this = "<<this<<endl;
}

CDate::CDate(const CDate& date){
    m_year = date.m_year;//这个其实是值传递，但是俩个this指针不一样，也可以理解为一种深拷贝（新地址+内容）
    m_mon = date.m_mon;//其实就是拷贝对象的this指针的成员，将原对象this指针的成员赋值给拷贝的对象this指针的成员
    m_day = date.m_day;
    //str = date.str;这个就是浅拷贝，因为str是char*，是字符串首个地址，会导致指向同一个内存
    str = new char[MAX_NEW_MEM];
    cout<<"Calling Copy Constructor"<<",this = "<<this<<",Copy Data"<<endl;
}

CDate::CDate(CDate&& date) noexcept{
    m_year = date.m_year;
    m_mon = date.m_mon;
    m_day = date.m_day;
    str = date.str;
    date.str = NULL;
    cout<<"Calling Move Constructor"<<",this = "<<this<<endl;
}

CDate::~CDate(){
    cout<<"Calling Destructor"<<",this = "<<this<<endl;
    delete [] str;
}

//第一个CDate是类型
CDate CDate::operator+(int day){
    //这里用到了拷贝构造函数（深拷贝——新地址+内容），拷贝构造函数都会是新地址（新的对象，拷贝构造函数是用来初始化同类型的新对象的）
    CDate temp = *this;
    temp.m_day += day;
    cout<<"Calling operator+"<<",this = "<<&temp<<endl;
    return temp;//返回临时对象
    //临时对象只会在程序中很短暂的停留，使用完之后会被立即销毁
}

int main(){
    CDate date(2024,06,07);//调用构造函数
    cout<<endl;

    //date.operator+(1)这里先是去拷贝构造函数去构造局部变量temp，完成后返回temp临时对象后销毁（析构）
    //所以：std::cout<<&(date+1)<<std::endl;这个写法错误——完成date.operator+(1)操作就已经销毁temp的地址了（临时对象销毁）
    CDate date1 = std::move(date+1);//std::move强制将date+1的求值结果转换为右值（date1用移动构造接管）
    //C++11标准通过右值引用来完全地接管这些临时对象，然后将临时对象的资源移动到接收对象
    date1.show();

    cout<<endl;

    return 0;
}