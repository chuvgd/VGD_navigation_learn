#include <iostream>
#include <Eigen/Dense>

int main(){
    //特殊矩阵生成函数能快速生成特定类型的矩阵，Zero()可以生成全部为0的矩阵
    //Identity()函数可以生成单位矩阵
    //Random()函数可以生成随机矩阵
    Eigen::Matrix3d zeroMatrix = Eigen::Matrix3d::Zero();
    Eigen::Matrix3d IdentityMatrix = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d RandomMatrix = Eigen::Matrix3d::Random();
    std::cout<<"Zero matrix:\n"<<zeroMatrix<<std::endl;
    std::cout<<"Identity matrix:\n"<<IdentityMatrix<<std::endl;
    std::cout<<"Random matrix:\n"<<RandomMatrix<<std::endl;

    return 0;
}