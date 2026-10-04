#include <iostream>
#include <cstring>

//对应函数指针类型：
//eg.int (*)(int a , int b);
const char* func(const char* p1 , const char* p2){
    int i = 0;
    i = strcmp(p1 , p2);//strcmp是用来比较两个字符串大小
    //strcmp函数，参数1：指向第一个字符串指针；参数2：指向第二个字符串指针
    //返回值：按照ASCII码表的顺序逐个字符去进行比较
    //等于0：相等；大于0：str1大于str2；小于0：str1小于str2
    if( 0 == i){
        std::cout<<"相等"<<std::endl;
        return p1;
    }else{
        std::cout<<"不相等"<<std::endl;
        return p2;
    }
}

int main(){
    //调用函数
    const char* (*pf)(const char* p1 , const char* p2);//定义一个指向函数的指针，最左边的char*是函数返回值类型，而*表示pf是一个指针
    //参数名可以去掉，这样就是指针p可以保存函数类型为const char*的俩个参数，返回值是const char*
    pf = &func;
    //pf = func;这种写法也是可以的，因为函数名被编译值后就是一个地址
    (*pf)("ac","bc");
    //字符串字面量是const char[N]
    
    return 0;
}