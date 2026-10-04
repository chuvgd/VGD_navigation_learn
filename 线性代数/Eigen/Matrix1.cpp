#include <iostream>
#include <Eigen/Dense>

int main(){
    //固定尺寸矩阵声明(3*3矩阵且元素是double)
    Eigen::Matrix3d fixedMatrix;
    //动态矩阵声明
    Eigen::MatrixXd dynamicMatrix(2,3);

    std::cout<<"Fixed matrix rows:"<<fixedMatrix.rows()<<",cols:"<<fixedMatrix.cols()<<std::endl;
    std::cout<<"Dynamic matrix rows:"<<dynamicMatrix.rows()<<",cols:"<<dynamicMatrix.cols()<<std::endl;

    return 0;
}