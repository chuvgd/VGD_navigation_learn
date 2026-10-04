#include <iostream>
#include <cmath>
#include <Eigen/Dense>

// template<typename T>
//     class Add{
//         public:
//             T a;
//             T b;
//             T add(){
//                 return a+b;
//             }
//     };

int main(int argc,char* argv[]){
    //初始化：旋转角和旋转轴
    double alpha = M_PI / 4;//旋转角——45度
    Eigen::Vector3d axis(0,0,1);//绕z轴旋转
    Eigen::AngleAxisd rotation_verctor(alpha,axis);

    // Add<int> vgd;
    // vgd.a = 1;
    // vgd.b = 2;
    //也可以直接使用单位轴，如：绕着z轴
    // Eigen::Vector3d::UnitZ()

    std::cout<<"rotation angle = :"<<rotation_verctor.angle() * 180/M_PI<<"deg"<<std::endl;
    std::cout<<"rotation_aix = :"<<rotation_verctor.axis().transpose()<<std::endl;

    //旋转向量取出就是一个3*1向量：轴✖角
    Eigen::Vector3d revc = rotation_verctor.angle()*rotation_verctor.axis();
    std::cout<<"rotation vector(3*1):"<<revc.transpose()<<std::endl;

    //旋转向量转旋转矩阵
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix = rotation_verctor.matrix();
    //写法1
    // rotation_matrix = rotation_verctor.toRotationMatrix();
    //写法2
    std::cout<<"rotation matrix:\n"<<rotation_matrix<<std::endl;

    //旋转向量转欧拉角
    //eulerAngles(0,1,2)表示按照x-y-z顺序拆解，返回值单位是弧度
    Eigen::Vector3d eulerAngle = rotation_matrix.matrix().eulerAngles(0,1,2);
    std::cout<<"euler angles(rad):"<<eulerAngle.transpose()<<std::endl;
    std::cout<<"euler angles(deg):"<<(eulerAngle*180/M_PI).transpose()<<std::endl;

    //旋转向量转四元数
    Eigen::Quaterniond quaternion(rotation_verctor);//写法一：构造函数
    // Eigen::Quaterniond quaternion;
    // quaternion = rotation_matrix;
    //直接赋值
    std::cout<<"quaternion (x,y,z,w):"<<quaternion.coeffs().transpose()<<std::endl;

    //用旋转向量旋转一个点
    Eigen::Vector3d p(1,0,0);
    Eigen::Vector3d p_rotated = rotation_verctor * p;//旋转向量✖
    Eigen::Vector3d p_rotated_mat = rotation_matrix * p;//旋转矩阵✖
    std::cout<<"point(1,0,0) rotated:\n"<<p_rotated.transpose()<<std::endl;
    std::cout<<"check with matrix:\n"<<p_rotated_mat.transpose()<<std::endl;

    return 0;
}