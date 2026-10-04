#include <Eigen/Dense>
#include <iostream>
#include <cmath>

int main(int argc,char* argv[]){
    //初始化旋转矩阵
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix<<0,-1,0,
                     1,0,0,
                     0,0,1;
    std::cout<<"旋转矩阵:"<<rotation_matrix<<std::endl;

    //旋转矩阵转旋转向量
    Eigen::AngleAxisd rotation_vector(rotation_matrix);
    //方式1
    // Eigen::AngleAxisd rotation_vector;
    // rotation_vector = rotation_matrix;
    // //方式2
    // Eigen::AngleAxisd rotation_vector;
    // rotation_vector.fromRotationMatrix(rotation_matrix);
    // //方式3
    std::cout<<"旋转向量的转动角度:"<<rotation_vector.angle()*180/M_PI<<std::endl;
    std::cout<<"旋转向量的转动轴:"<<rotation_vector.axis().transpose()<<std::endl;

    //旋转矩阵转欧拉角
    //绕着xyz的方式输出转过的角度的矩阵（rad）
    Eigen::Vector3d eulerAngle = rotation_matrix.eulerAngles(0,1,2);
    std::cout<<"欧拉角为:"<<eulerAngle.transpose()<<std::endl;

    //旋转矩阵转四元数
    Eigen::Quaterniond quaternion(rotation_matrix);
    //方式1
    // Eigen::Quaterniond quaternion;
    // quaternion = rotation_matrix;
    // //方式2
    std::cout<<"四元数:"<<quaternion.coeffs().transpose()<<std::endl;

    return 0;
}