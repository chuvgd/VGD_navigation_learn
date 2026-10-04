cmake_minimum_required(VERSION 3.15)

project(Eigen)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(Matrix1 Matrix1.cpp)
add_executable(Matrix2 Matrix2.cpp)
add_executable(Matrix3 Matrix3.cpp)
add_executable(Matrix4 Matrix4.cpp)
add_executable(Matrix5 Matrix5.cpp)
add_executable(Matrix6 Matrix6.cpp)
add_executable(Matrix7 Matrix7.cpp)
add_executable(Vector1 旋转向量1.cpp)
add_executable(Rotation_Matrix 旋转矩阵.cpp)
add_executable(Euler_Angles 欧拉角1.cpp)
add_executable(slam slam.cpp)

