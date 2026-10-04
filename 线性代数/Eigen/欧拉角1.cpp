#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main(){
    const double d2r = M_PI/180.0;//角度转弧度
    double roll = 45*d2r;
    double pitch = 45*d2r;
    double yaw = 45*d2r;
    Eigen::Vector3d eulerAngle(roll,pitch,yaw);
    std::cout<<"欧拉角："<<eulerAngle.transpose()/d2r<<std::endl;

    //欧拉角转旋转向量，旋转矩阵，四元数
    Eigen::AngleAxis rollAngle(eulerAngle(0),Eigen::Vector3d::UnitX());
    Eigen::Matrix3d rotation_matrix1 = rollAngle.toRotationMatrix();
    std::cout<<"第一次旋转矩阵："<<rotation_matrix1<<std::endl;
    Eigen::AngleAxis pitchAngle(eulerAngle(1),Eigen::Vector3d::UnitY());
    Eigen::Matrix3d rotation_matrix2 = (pitchAngle*rollAngle).toRotationMatrix();
    std::cout<<"第二次旋转矩阵："<<rotation_matrix2<<std::endl;
    Eigen::AngleAxis yawAngle(eulerAngle(2),Eigen::Vector3d::UnitZ());
    Eigen::Matrix3d rotation_matrix3 = (yawAngle*pitchAngle*rollAngle).toRotationMatrix();
    std::cout<<"第三次旋转矩阵："<<rotation_matrix3<<std::endl;

    //轴角是绕世界坐标系

    //注意：两个旋转向量相✖会返回四元数
    //世界坐标系下的zyx
    auto q = rollAngle*pitchAngle*yawAngle;
    //按照的是外旋的zyx的角度
    Eigen::Matrix3d rotation_matrix = q.toRotationMatrix();
    Eigen::AngleAxisd rotation_vector(q);

    std::cout << "旋转矩阵:\n" << rotation_matrix << std::endl;
    std::cout << "旋转向量: 角度 = " << rotation_vector.angle()/d2r << " 度, 轴 = "
              << rotation_vector.axis().transpose() << std::endl;
    std::cout << "四元数 (x,y,z,w) = " << q.coeffs().transpose() << std::endl;

    //尝试反推出欧拉角角度
    Eigen::Vector3d eulerAngle1 = rotation_matrix.eulerAngles(0,1,2);
    //按照xyz输出相关的roll-pitch-yaw相关角度
    std::cout<<"外推出的欧拉角:"<<eulerAngle1.transpose()*180/M_PI<<std::endl;

    return 0;
}