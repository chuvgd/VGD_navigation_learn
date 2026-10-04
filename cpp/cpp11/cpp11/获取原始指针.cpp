#include <iostream>
#include <cstring>
#include <memory>

int main(){
    int len = 128;
    std::shared_ptr<char> ptr(new char[len]);
    //得到指针的原始地址
    char* add = ptr.get();
    memset(add , 0 , len);
    strcpy(add,"我是要成为海贼王的男人!!!");
    std::cout<<"string:"<<add<<std::endl;

    std::shared_ptr<int> p(new int);
    *p = 100;
    std::cout<<*p.get()<<" "<<*p<<std::endl;

    return 0;
}