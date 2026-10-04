#include <iostream>
#include <cmath>
#include <Eigen/Dense>

// 对应笔记「核心：Eigen库计算位姿变换 —— 1. 旋转向量」的函数调用demo
// 头文件用 Eigen/Dense 即可，它已经包含了 Core 和 Geometry 模块

int main(){
    // ---------- 1. 初始化：旋转角 + 旋转轴 ----------
    double alpha = M_PI / 4;                        // 旋转角，此处为45度
    Eigen::Vector3d axis(0, 0, 1);                  // 绕z轴旋转
    Eigen::AngleAxisd rotation_vector(alpha, axis);

    // 也可以直接用单位轴，例如绕z轴：Eigen::AngleAxisd(alpha, Eigen::Vector3d::UnitZ());
    // 注意：笔记里写的 UintZ() 是笔误，正确写法是 UnitZ()

    std::cout << "rotation angle = " << rotation_vector.angle() * 180 / M_PI << " deg\n";
    std::cout << "rotation axis  = " << rotation_vector.axis().transpose() << "\n\n";

    // 旋转向量取出来就是一个 3x1 的向量：轴 * 角
    Eigen::Vector3d rvec = rotation_vector.angle() * rotation_vector.axis();
    std::cout << "rotation vector (3x1): " << rvec.transpose() << "\n\n";

    // ---------- 2. 旋转向量 -> 旋转矩阵 ----------
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix = rotation_vector.matrix();     // 写法一：matrix()
    // rotation_matrix = rotation_vector.toRotationMatrix();  // 写法二：toRotationMatrix()
    std::cout << "rotation matrix:\n" << rotation_matrix << "\n\n";

    // ---------- 3. 旋转向量 -> 欧拉角 ----------
    // eulerAngles(0,1,2) 表示按 x-y-z 的顺序拆解，返回值单位是弧度
    Eigen::Vector3d eulerAngle = rotation_vector.matrix().eulerAngles(0, 1, 2);
    std::cout << "euler angles (rad): " << eulerAngle.transpose() << "\n";
    std::cout << "euler angles (deg): " << (eulerAngle * 180 / M_PI).transpose() << "\n\n";

    // ---------- 4. 旋转向量 -> 四元数 ----------
    Eigen::Quaterniond quaternion(rotation_vector); // 写法一：构造函数
    // Eigen::Quaterniond quaternion;               // 写法二：直接赋值
    // quaternion = rotation_vector;
    std::cout << "quaternion (x,y,z,w): " << quaternion.coeffs().transpose() << "\n\n";

    // ---------- 5. 用旋转向量旋转一个点 ----------
    Eigen::Vector3d p(1, 0, 0);
    Eigen::Vector3d p_rotated = rotation_vector * p;            // 直接用旋转向量乘
    Eigen::Vector3d p_rotated_mat = rotation_matrix * p;        // 用旋转矩阵乘
    std::cout << "point (1,0,0) rotated:\n" << p_rotated.transpose() << "\n";
    std::cout << "check with matrix:\n" << p_rotated_mat.transpose() << "\n";

    return 0;
}
