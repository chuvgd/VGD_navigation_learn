#include <iostream>

//new的基本语法
int* func(){
    //在堆区创建整形数据
    //new返回的是该数据类型的指针
    int* p=new int(10);
    return p;
}

void test01(){
    int* p=func();
    std::cout<<*p<<std::endl;
    std::cout<<*p<<std::endl;
    //堆区的数据：由程序员管理开辟和释放
    //如果想释放堆区的数据，利用关键字delete
    delete p;
    //std::cout<<*p<<std::endl;

}

void test02(){
    //创建10整形数据的数组，在堆区
    int* arr=new int[10];//10代表数组有10个元素
    //返回的是数组的首地址

    for(int i=0;i<10;i++){
        arr[i]=i+100;//给10个元素赋值
    }

    for(int i=0;i<10;i++){
        std::cout<<arr[i]<<std::endl;
    }
    //释放堆区数组
    //释放数组：需要加[]才可以
    delete[] arr;
}

int main(){
    test01();
    test02();
    return 0;
}