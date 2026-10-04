#include <iostream>
#include <functional>

void output(int x,int y){
    std::cout<<x<<" "<<y<<std::endl;
}

int main(){
    //使用绑定器绑定可调用对象和参数，并调用得到的仿函数
    std::bind(output,1,2)();
    std::bind(output,std::placeholders::_1,2)(10);
    std::bind(output,2,std::placeholders::_1)(10);

    std::bind(output,2,std::placeholders::_2)(10,20);

    std::bind(output,std::placeholders::_1,std::placeholders::_2)(10,20);

    return 0;
}