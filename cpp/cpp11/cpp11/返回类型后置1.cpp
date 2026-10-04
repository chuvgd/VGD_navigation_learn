#include <iostream>
using namespace std;

int& test(int& i){
    return i;
}

double test(double& d){
    d = d+100;
    return d;
}//函数重载

template<typename T>
//返回类型后置于语法
auto myFunc(T& t) -> decltype(test(t)){
    return test(t);
}

int main(){
    int x = 520;
    double y = 13.14;
    auto z1 = myFunc<int>(x);
    cout<<"z1 = "<<z1<<endl;
    auto z2 = myFunc<double>(y);
    cout<<"z2 = "<<z2<<endl;

    return 0;
}
