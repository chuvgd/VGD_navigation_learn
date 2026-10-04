#include <iostream>
#include <memory>

std::unique_ptr<int> func(){
    return std::unique_ptr<int>(new int(520));
}

int main(){
    //通过构造函数去初始化
    std::unique_ptr<int> ptr(new int(10));
    //通过转移所有权的方式初始化
    std::unique_ptr<int> ptr1 = std::move(ptr);
    std::unique_ptr<int> ptr2 = func();
    //这个通过函数返回独占指针可以其实是因为函数的块作用域在执行完后自动销毁，返回的是复制的临时变量，在给接收对象之后也会被销毁
    //这个func函数的独占指针只有在执行函数的时候在堆上开辟了520这个数据，函数执行完毕自动释放，通过接收对象其实是复制一份临时返回对象的值给接收对象（有点像拷贝构造函数）

    return 0;
}