#include <iostream>
#include <string>

using namespace std;

template <typename R = int ,typename N>
R func(N arg){
    return arg;
}

int main(){
    auto ret1 = func(520);
    cout<<"return value_1:"<<ret1<<endl;

    auto ret2 = func<double>(52.146);
    cout<<"return value_2:"<<ret2<<endl;
    //函数的返回值指定为double类型,函数参数是通过实参推导出来的，为double类型

    auto ret3 = func<int>(52.146);
    cout<<"return value_3:"<<ret3<<endl;

    auto ret4 = func<char , int>(100);
    cout<<"return value_4:"<<ret4<<endl;
}