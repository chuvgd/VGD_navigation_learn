#include <iostream>

template<typename T>
void printValue(T& t){
    std::cout<<"l-value:"<<t<<std::endl;
}

template<typename T>
void printValue(T&& t){
    std::cout<<"r-value:"<<t<<std::endl;
}

template<typename T>
void testForward(T&& v){
    printValue(v);
    //已经命名的右值v，编译器会视为左值处理，实际参数为左值
    printValue(std::move(v));
    //std::move把已经视作左值的再次转换为右值
    printValue(std::forward<T>(v));
    //std::forward<T>(v)按照T模板参数类型来处理
    std::cout<<std::endl;
}

int main(){
    //实际参数为右值，初始化后被推导成右值引用
    testForward(520);
    int num = 1314;
    testForward(num);
    testForward(std::forward<int>(num));
    //std::forward的模板T只有是左值引用类型时候，t才会被转换为T类型的左值
    //其他情况下是转换成T类型的右值
    testForward(std::forward<int&>(num));
    testForward(std::forward<int&&>(num));

    return 0;
}