#include <iostream>
#include <Eigen/Dense>

int main(){
    Eigen::Matrix2d mat;
    mat<< 1,2,
          3,4;
    
    std::cout<<"Inverse matrix:\n"<<mat.inverse()<<std::endl;
    std::cout<<"Determinant:\n"<<mat.determinant()<<std::endl;
    //矩阵的迹是方阵主对角线上元素的和
    std::cout<<"Trace:\n"<<mat.trace()<<std::endl;

    return 0;
}