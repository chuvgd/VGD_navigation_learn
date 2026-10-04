#include <iostream>

using namespace std;

//查询数组最大值函数的模板
// template <class T>
template <typename T>
//或者是typename T,这里的class或者typename是表示这里声明一个类型参数，即T
//这里更推荐是typename
T Max(T* a , int size)//类型参数T 模板名(形式参数表)——泛性函数
//size是数组元素个数
{
    T tmpMax = a[0];
    for(int i = 0 ; i < size; ++i){
        if(tmpMax < a[i]){
            tmpMax = a[i];
        }
    }
    return tmpMax;
}

int main(){
    int a[] = {1,2,4,5,7,8};
    int max;
    max = Max<int>(a , sizeof(a)/sizeof(int));
    std::cout<<"输出的元素大小:"<<max<<std::endl;
    //对模板实例化——就是函数类，函数类进行实例化相应类型的函数

    double b[] = {1.2,1.3,4.5,5.6};
    double max1;
    max1 = Max<double>(b , sizeof(b)/sizeof(double));
    std::cout<<"输出的元素大小:"<<max1<<std::endl;

    return 0;
}