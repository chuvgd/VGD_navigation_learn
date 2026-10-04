#include <iostream>

class Test{
public:
    Test(){};
    Test(int max){
        this -> m_max = max > 0 ? max : 100;
    }

    Test(int max , int min):Test(max){
        this -> m_min = min > 0 && min < max ? min : 1;
    }

    Test(int max , int min ,int mid):Test(max , min){
        this -> m_middle = mid < max && mid > min ? mid : 50;
    }

    int m_min;
    int m_max;
    int m_middle;
};

int main(){
    Test t(90,30,60);
    std::cout<<"min:"<<t.m_min<<",middle:"<<t.m_middle<<",max:"<<t.m_max<<std::endl;

    return 0;
}