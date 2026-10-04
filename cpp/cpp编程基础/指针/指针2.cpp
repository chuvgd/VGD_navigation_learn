#include <iostream>

int main(){
    int a = 10;

    int* p = &a;

    std::cout<<"sizeof(int*)="<<sizeof(int*)<<std::endl;
    std::cout<<"sizeof(float*)="<<sizeof(float*)<<std::endl;
    std::cout<<"sizeof(double*)="<<sizeof(double*)<<std::endl;
    std::cout<<"sizeof(char*)="<<sizeof(char*)<<std::endl;

    return 0;
}