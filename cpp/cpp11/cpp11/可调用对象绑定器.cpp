#include <iostream>
#include <functional>

void callFunc(int x , const std::function<void(int)> &f){
    if(x%2 == 0){
        f(x);
    }
}

void output(int x){
    std::cout<<x<<" ";
}

void output_add(int x){
    std::cout<<x+10<<" ";
}

int main(){
    //使用绑定器绑定可调用对象和参数
    auto f1 = std::bind(output , std::placeholders::_1);
    for(int i = 0;i<10;++i){
        callFunc(i , f1);
    }
    std::cout<<std::endl;

    auto f2 = std::bind(output_add , std::placeholders::_1);
    for(int i = 0;i<10;++i){
        callFunc(i , f2);
    }
    std::cout<<std::endl;

    return 0;
}
