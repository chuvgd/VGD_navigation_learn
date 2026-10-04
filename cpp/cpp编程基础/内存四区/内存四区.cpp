#include <iostream>

//创建全局变量（在函数体外即为全局变量）
int g_a=10;
int g_b=20;

//const修饰的变量——有类型的常量
//const修饰的全局变量
const int c_g_a=10;
const int c_g_b=10;


int main(int argc,char *argv[]){
    //创建普通局部变量（在函数体内的变量都是局部变量）
    int a=10;
    int b=20;

    //静态常量：在普通常量前加上static关键字
    static int s_a=10;
    static int s_b=20;

    //const修饰的局部变量（属于非全局区）
    const int c_a=10;
    const int c_b=10;

    //c_g_a=20是会进行报错的，因为const修饰之后就是一个常量，它只可读，不可进行修改

    std::cout<<"a的地址:"<<(long long)&a<<std::endl;
    std::cout<<"b的地址:"<<(long long)&b<<std::endl;

    std::cout<<"g_a的地址:"<<(long long)&g_a<<std::endl;
    std::cout<<"g_b的地址:"<<(long long)&g_b<<std::endl;

    std::cout<<"s_a的地址:"<<(long long)&s_a<<std::endl;
    std::cout<<"s_b的地址:"<<(long long)&s_b<<std::endl;

    //字符串常量
    std::cout<<"字符串常量的地址:"<<(long long)&"hello world"<<std::endl;

    std::cout<<"c_g_a的地址:"<<(long long)&c_g_a<<std::endl;
    std::cout<<"c_g_b的地址:"<<(long long)&c_g_b<<std::endl;

    std::cout<<"c_a的地址:"<<(long long)&c_a<<std::endl;
    std::cout<<"c_b的地址:"<<(long long)&c_b<<std::endl;

    //在64位系统上,指针是64位,而 int 只有32位，用 (int)&a 强转地址会截断高位,编译器默认把它当作错误
    //这里&a等其实就是指针，因为符合指向变量的内存地址的定义，其实就是int* p=&a;
    //&a是取地址表达式，它的类型是int*（指向int的指针），它的值就是a的地址
    //所以说，int* p=&a就是把&a这个指针值（地址值）存进指针变量p里

    //这里在进行对于字节和进制的解释：字节/位是“容量单位”，进制是写数字的方式
    //地址本质是一个数字,代表"这是内存里第几个字节"，与按照何种进制无关
    //1字节=8位，2的8次方，有256种状态
    //无符号和有符号的约定不同：计算方式——最高位（0是非负，1是负数）


    return 0;
}