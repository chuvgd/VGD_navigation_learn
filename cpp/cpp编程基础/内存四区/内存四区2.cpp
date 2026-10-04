#include <iostream>

int* func(){
   //利用new关键字，可以将数据开辟到堆区
   //指针本质也是局部变量，放在栈上，指针保存的数据是在堆上
   int* p=new int(10);
   return p;//返回的是int类型变量的地址，p本身存储的值是new int(10)的地址
}

int main(){
    //这里是执行完一次func()，局部指针变量p(在func()中的)被栈区直接释放，但是在main()中又创建了局部指针变量接住了返回的函数指针变量，main中的指针变量p指向堆区的数据new int(10)
    //func()中的p是局部指针变量，本身存在在栈区，执行函数返回值后这个指针变量被释放
    //main()里新建了一个局部指针变量p，接住了返回的地址值
    //注意：p变量本身在栈上被释放了，但它保存的那个地址指向堆区，堆区数据不受函数结束影响（自己开辟，自己释放，如果自己忘记释放，程序结束后操作系统统一释放）
    int* p=func();

    std::cout<<*p<<std::endl;
    std::cout<<*p<<std::endl;
    std::cout<<*p<<std::endl;
    std::cout<<*p<<std::endl;


    return 0;
}