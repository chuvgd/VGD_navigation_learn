#include <iostream>

//不要返回局部变量的引用
// int& test01(){
//     int a = 10;//局部变量（栈上）
//     return a;//等价于int &别名 = a;然后把引用作为返回值return回去
// }

int& test02(){
    static int a = 10;//静态变量，存放在全局区下，全局区上的数据在程序结束后系统释放
    return a;
}

int main(){
    // int &ref = test01();

    // std::cout<<"ref = "<<ref<<std::endl;//未定义行为，对已经销毁的内存进行访问，编译器给出警告，运行时结果不可预测
    // std::cout<<"ref = "<<ref<<std::endl;

    int &ref2 = test02();//ref2是b的别名，即ref2也是a的别名，对于原对象a现在有两个别名
    std::cout<<"ref2 = "<<ref2<<std::endl;

    test02() = 1000;
    //返回的是函数的引用，可以作为左值进行操作，其实本质就是int &b = a;把b返回（不同于值返回是返回的值，引用返回的是就是a的别名b);然后直接对b进行赋值操作
    std::cout<<"ref2 = "<<ref2<<std::endl; 

    return 0;
}