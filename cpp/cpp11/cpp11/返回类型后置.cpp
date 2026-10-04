#include <iostream>

using namespace std;

template<typename R , typename T , typename U>
R add(T t , U u){
    return t+u;
}

int main(){
    int x = 520;
    double y = 13.14;
    auto z = add<decltype(x+y),int,double>(x,y);
    cout<<"z:"<<z<<endl;

    return 0;
}

// template <typename T, typename U>
// decltype(t+u) add(T t, U u)
// {
//     return t + u;
// }
//这种写法是不允许的，因为变量一开始还没有存在