#include <iostream>
using namespace std;

class Test{
public:
    Test(){};
    Test(int max){
        this -> m_max = max > 0 ? max : 100;
    }

    Test(int max , int min){
        this -> m_max = max > 0 ? max : 100;//冗余代码
        this -> m_min = min > 0 && min < max ? min : 1;
    }

    Test(int max , int min , int mid){
        this -> m_max = max > 0 ? max : 100;//冗余代码
        this -> m_min = min > 0 && min < max ? min : 1;//冗余代码
        this -> m_middle = mid < max && mid > min ? mid : 50;
    }

// private:
    int m_max;
    int m_min;
    int m_middle;
};

int main(){
    Test t(90,30,60);
    std::cout<<"min:"<<t.m_min<<",middle:"<<t.m_middle<<",max:"<<t.m_max<<std::endl;

    return 0;
}

//这里三个构造函数，但是这三个构造函数有重复的代码，在cpp11之前构造函数是不能调用构造函数的，但是委托之后：
//代码可以用委托构造函数优化