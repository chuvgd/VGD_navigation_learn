#include <iostream>
#include <cmath>
#include <Eigen/Dense>

/* 欧拉角 demo（对应 Eigen.md 的 “3. 欧拉角（统一认为是内旋）”）
 *
 * 约定：
 *   eulerAngle = (roll, pitch, yaw) = 绕 x / y / z 轴转过的角度，单位是弧度
 *   组合方式：R = Rz(yaw) * Ry(pitch) * Rx(roll)，也就是常说的“内旋 ZYX”
 *   内旋：每次都绕“转完之后”的自身轴转（轴会跟着动）
 *         它等价于“外旋 XYZ”：先绕世界 x 转 roll，再绕世界 y 转 pitch，最后绕世界 z 转 yaw
 *   反解：用 eulerAngles(2,1,0)，返回顺序是 (yaw, pitch, roll)
 */

int main(){
    const double d2r = M_PI / 180.0;   // 角度 -> 弧度

    // ===== 1. 初始化欧拉角 (roll, pitch, yaw) =====
    double roll = 30 * d2r, pitch = 20 * d2r, yaw = 40 * d2r;
    Eigen::Vector3d eulerAngle(roll, pitch, yaw);
    std::cout << "欧拉角 (roll,pitch,yaw) = " << eulerAngle.transpose()/d2r << " 度" << std::endl;

    // ===== 2. 欧拉角 -> 旋转向量 / 旋转矩阵 / 四元数 =====
    // 先拆成三个单轴旋转，再按 yaw*pitch*roll 的顺序乘起来
    Eigen::AngleAxisd rollAngle (eulerAngle(0), Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd pitchAngle(eulerAngle(1), Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd yawAngle  (eulerAngle(2), Eigen::Vector3d::UnitZ());

    // 注意：Eigen 里 AngleAxis 乘 AngleAxis 的结果是四元数
    Eigen::Quaterniond quaternion = yawAngle * pitchAngle * rollAngle;
    Eigen::Matrix3d    rotation_matrix = quaternion.toRotationMatrix();   // 旋转矩阵
    Eigen::AngleAxisd  rotation_vector(quaternion);                      // 旋转向量（也可写成 AngleAxisd(rotation_matrix)）

    std::cout << "旋转矩阵:\n" << rotation_matrix << std::endl;
    std::cout << "旋转向量: 角度 = " << rotation_vector.angle()/d2r << " 度, 轴 = "
              << rotation_vector.axis().transpose() << std::endl;
    std::cout << "四元数 (x,y,z,w) = " << quaternion.coeffs().transpose() << std::endl;

    // ===== 3. 反解：旋转矩阵 -> 欧拉角 =====
    // 参数要跟前面的组合方式对应：(2,1,0) 表示内旋 Z->Y->X，返回 (yaw, pitch, roll)
    Eigen::Vector3d ea = rotation_matrix.eulerAngles(2,1,0);
    std::cout << "\n反解 (yaw,pitch,roll) = " << ea.transpose()/d2r
              << " 度   <- 还原出了 40,20,30" << std::endl;

    // 换成 (0,1,2) 也能描述同一个旋转，只是得到另一组角
    Eigen::Vector3d ea2 = rotation_matrix.eulerAngles(0,1,2);
    std::cout << "换用 (0,1,2) 反解     = " << ea2.transpose()/d2r
              << " 度   <- 数值不同，但描述的是同一个旋转" << std::endl;

    // ===== 4. 为什么要强调“约定”：同样三个角，解释不同结果就不同 =====
    // 上面用的是内旋 ZYX：Rz(yaw)*Ry(pitch)*Rx(roll)
    // 如果误按“内旋 XYZ”来理解（即 Rx(roll)*Ry(pitch)*Rz(yaw)），得到的是另一个旋转：
    Eigen::Matrix3d other = (Eigen::AngleAxisd(roll,  Eigen::Vector3d::UnitX())
                           * Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY())
                           * Eigen::AngleAxisd(yaw,   Eigen::Vector3d::UnitZ())).toRotationMatrix();
    std::cout << "\n按“内旋 XYZ”理解时的偏差 = " << (other - rotation_matrix).norm()
              << "   <- 不为 0，所以欧拉角必须绑定约定" << std::endl;

    // ===== 5. 万向锁：pitch = ±90° 时 roll 和 yaw 会混在一起，解不唯一 =====
    Eigen::Vector3d lockAngle(30*d2r, 90*d2r, 40*d2r);   // pitch 拉到 90 度
    Eigen::Matrix3d lockR = (Eigen::AngleAxisd(lockAngle(2), Eigen::Vector3d::UnitZ())
                           * Eigen::AngleAxisd(lockAngle(1), Eigen::Vector3d::UnitY())
                           * Eigen::AngleAxisd(lockAngle(0), Eigen::Vector3d::UnitX())).toRotationMatrix();

    Eigen::Vector3d lockBack = lockR.eulerAngles(2,1,0);
    std::cout << "\n万向锁: 输入 (roll,pitch,yaw) = 30,90,40 度" << std::endl;
    std::cout << "        反解 (yaw,pitch,roll) = " << lockBack.transpose()/d2r
              << " 度   <- 和输入对不上了" << std::endl;

    Eigen::Matrix3d lockCheck = (Eigen::AngleAxisd(lockBack(0), Eigen::Vector3d::UnitZ())
                               * Eigen::AngleAxisd(lockBack(1), Eigen::Vector3d::UnitY())
                               * Eigen::AngleAxisd(lockBack(2), Eigen::Vector3d::UnitX())).toRotationMatrix();
    std::cout << "        重建误差 = " << (lockCheck - lockR).norm()
              << "   <- 旋转本身是对的，只是角不唯一" << std::endl;

    return 0;
}
