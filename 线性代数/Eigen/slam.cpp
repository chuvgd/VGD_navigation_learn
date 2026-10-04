#include <iostream>
#include <ctime>
//Eigen核心部分
#include <Eigen/Core>
//Eigen稠密矩阵代数运算（逆，特征值等）
#include <Eigen/Dense>

#define MATRIX_SIZE 50

//演示Eigen基本类型的使用——来自视觉slam14讲

int main(int argc,char* argv[]){
    //Eigen中所有的向量和矩阵都是Eigen::Matrix，它是一个模板类，前三个参数为：数据类型，行，列
    //声明一个2*3的float矩阵
    Eigen::Matrix<float,2,3> matrix_23;

    //同时，Eigen通过typedef提供了很多内置类型，不过都是Eigen::Matrix
    //eg.Vector3d实际上是Eigen::Matrix<double,3,1>，即三维向量
    Eigen::Vector3d v_3d;
    Eigen::Matrix<double,3,1> vd_3d;
    //typedef Eigen::Matrix<double, 3, 1> Eigen::Vector3d
    //Matrix实际上是Eigen::Matrix<double,3,3>
    Eigen::Matrix3d Matrix_33;
    //初始化为0矩阵
    Matrix_33 = Eigen::Matrix3d::Zero();
    //如果矩阵大小不确定，可以使用动态大小的矩阵
    // Eigen::Matrix<double,Dynamic,Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x;

    //下面是对Eigen阵的操作
    //输入数据
    matrix_23<<1,2,3,4,5,6;
    //输出
    std::cout<<"matrix 2*3 :\n"<<matrix_23<<std::endl;

    //用()访问矩阵中的元素
    std::cout<<"print matrix 2*3 "<<std::endl;
    for(int i = 0;i<2;i++){
        for(int j = 0;j<3;j++){
            //访问矩阵中的元素，利用()，(col,rol),其下标规则和数组一致，如果是一维矩阵（只有行向量或者列向量），可以用[]
            std::cout<<matrix_23(i,j);
        }
        std::cout<<std::endl;
    }

    v_3d<<1,2,3;
    vd_3d<<4,5,6;

    for(int i = 0;i<3;i++){
        std::cout<<v_3d(i)<<"\t";
    }

    for(int i = 0;i<3;i++){
        std::cout<<vd_3d[i]<<"\t";
        // std::cout<<std::endl;
    }

    //在Eigen中不能混合使用不同类型的矩阵，这样是错误的
    //应该显式转换
    Eigen::Matrix<double,2,1> result = matrix_23.cast<double>()*v_3d;
    std::cout<<std::endl;
    std::cout<<"[1,2,3,4,5,6]*[1,2,3]:\n"<<result.transpose()<<std::endl;
    
    //同样的不能搞错矩阵的维度

    //一些矩阵运算
    // Eigen::Matrix3d matrix_331;
    // Eigen::Matrix3d matrix_33;
    // matrix_33 = matrix_331.Random();
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Random();
    //matrix_33.Random();//会出现奇怪的现象
    // matrix_33.Random();//随机数矩阵
    std::cout<<"random_matrix:"<<matrix_33<<std::endl;
    std::cout<<"transpose:\n"<<matrix_33.transpose()<<std::endl;//求矩阵的转置
    std::cout<<"sum:"<<matrix_33.sum()<<std::endl;//求矩阵各个元素的和
    std::cout<<"trace:"<<matrix_33.trace()<<std::endl;//求矩阵的迹
    std::cout<<"times 10:\n"<<10*matrix_33<<std::endl;//数乘
    std::cout<<"inverse:\n"<<matrix_33.inverse()<<std::endl;//求矩阵的逆
    std::cout<<"det:"<<matrix_33.determinant()<<std::endl;//求矩阵的行列式
}