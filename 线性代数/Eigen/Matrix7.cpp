#include <iostream>
#include <Eigen/Dense>

int main(){
    Eigen::Matrix3d A;
    A<<1,2,3,
       4,5,6,
       7,8,9;
    
    Eigen::Vector3d b(3,3,4);
    Eigen::Vector3d x = A.lu().solve(b);
    //lu求解线性方程组
    std::cout<<"Solution of the linear system:\n"<<x<<std::endl;

    return 0;
}