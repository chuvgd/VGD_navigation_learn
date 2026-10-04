#include <iostream>

//值传递
void swap01(int a,int b){
    int temp = a;
    a = b;
    b = temp;
    std::cout<<"a="<<a<<std::endl;
    std::cout<<"b="<<b<<std::endl;
}

//地址传递
void swap02(int* p1,int* p2){
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main(){
    //1.值传递
    int a = 10;
    int b = 20;
    swap01(a,b); 
    //值传递：只能修改函数内部形式参数的逻辑，因为值传递是拷贝一份实际参数，函数执行完毕后，函数栈上的数据被销毁，即被拷贝的实际参数被自动释放，但是实际参数没有发生改变
    std::cout<<"a="<<a<<std::endl;
    std::cout<<"b="<<b<<std::endl;
    swap02(&a,&b);
    //地址传递：因为传入的参数是变量的地址，函数内部的逻辑是对于拿到的数据地址进行解引用来修改，其本质就是地址是确定的情况下，直接修改地址背后映射的值，对于形式参数p1和p2还是栈上变量用完就销毁，但是a和b是main()作用域下的变量，main()函数结束后才会进行销毁，所以直接传入地址修改地址其映射的值
    std::cout<<"a="<<a<<std::endl;
    std::cout<<"b="<<b<<std::endl;

    return 0;
}

//关键点：指针本身也是值传递（复制了一份相同的内存地址即指针），但是这个复制的指针仍然指向同一块内存，所以是把地址复制了一遍进行操作