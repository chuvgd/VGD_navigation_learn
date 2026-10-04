#include <iostream>

//交换函数
//1.值传递
void mySwap01(int a,int b){
    int temp = a;
    a = b;
    b =temp;
    std::cout<<"swap中的a= "<<a<<std::endl;
    std::cout<<"swap中的b= "<<b<<std::endl;
}
//对于值传递：形式参数是普通变量，在函数内部实际上是int a = a;前者a是形式参数，函数作用域开辟的栈上局部变量，是把从其他地方传入的实际参数的值拷进函数栈上变量a上，运行完毕之后自动释放函数栈上数据

//2.地址传递
void mySwap02(int* a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//对于地址传递：形式参数同样也是普通变量，和值传递同理，其实是int* a = &a，把a的地址拷贝进函数的栈上变量a中，但是指向的都是传入的参数的地址，所以解引用进行操作的时候是直接对传入实际参数的值进行操作，函数运行结束之后也是同样释放的是int* a

//3.引用传递
void mySwap03(int &a,int &b){
    //int &a = a;
    //int &b = b;
    //main中调用这个函数传入a和b实际参数之后，对实际参数起别名，实际上就是直接修改实际参数
    int temp = a;
    a = b;
    b = temp;
}
//对于引用传递：形式参数是对于传入实际参数的别名，即int &a = a，进行操作的行为也都是对同一块内存地址（只是对传入参数起别名而已），运行结束后也是把别名进行销毁

int main(){
    int a = 10;
    int b = 20;
    mySwap01(a,b);//值传递，形参不会修饰实参数
    std::cout<<"a= "<<a<<std::endl;
    std::cout<<"b= "<<b<<std::endl;
    std::cout<<std::endl;
    mySwap02(&a,&b);//地址传递，形式参数修饰了实际参数
    std::cout<<"a= "<<a<<std::endl;
    std::cout<<"b= "<<b<<std::endl;
    std::cout<<std::endl;
    mySwap03(a,b);//引用传递，形式参数修饰了实际参数
    std::cout<<"a= "<<a<<std::endl;
    std::cout<<"b= "<<b<<std::endl;
    std::cout<<std::endl;

    return 0;
}