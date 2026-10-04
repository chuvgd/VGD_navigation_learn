#include <iostream>
#include <Eigen/Dense>

int main(){
    Eigen::Matrix2d a;
    a<< 1,2,
        3,4;
    Eigen::Matrix2d b;
    b<< 2,3,
        1,4;
    
    std::cout<<"Matrix addition:\n"<<a + b<<std::endl;
    std::cout<<"Matrix subtraction:\n"<<a - b<<std::endl;
    std::cout<<"Element-wise multipication:\n"<<a.array() * b.array()<<std::endl;
    std::cout<<"Matrix multipication:\n"<<a * b<<std::endl;

    return 0;
}