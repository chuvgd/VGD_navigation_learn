#include <iostream>

using namespace std;

class Date{
    public:
        Date(int year = 19000,int month = 1,int day = 1){
            _year = year;
            _month = month;
            _day = day;
        }

        Date(const Date& d){
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }//这个就是体现拷贝，把原对象的成员数据拿过来进行复制一遍，但是它们是相互独立的，改变其中一个对象的数据成员的值不会影响另一个数据对象
    
    private:
        int _year;
        int _month;
        int _day;
};

int main(){
    Date d1;
    Date d2(d1);
    return 0;
}

//对于值传递：复制的是值的副本，不是数据本身（引用——其别名的机制）或者其地址副本（指针——对数据地址进行操作），如果值传递进行拷贝构造函数，会进行层层递归调用
//Date d2(d1)是按值传递的Date对象，所以进入函数体之前，要把实参d1拷贝一份，而拷贝d1这个动作本身需要调用拷贝构造函数，触发Date(const Date date)，再一次执行上一次的动作，一直递归下去，最后无法到函数体，引发栈溢出
//只有Date(const Date &date)是拷贝构造函数，对于值传递直接是非法声明，而Date(Date* p)就是普通构造函数——函数重载