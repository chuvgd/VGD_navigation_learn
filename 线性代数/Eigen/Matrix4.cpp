#include <iostream>
#include <Eigen/Dense>

//块操作与切片操作可用于提取矩阵的部分元素，使用block()函数可以提取矩阵的子块
int main(){
    Eigen::Matrix4f mat;
    mat<< 1,2,3,4,
          5,6,7,8,
          9,10,11,12,
          13,14,15,16;
    Eigen::Matrix2f subMat = mat.block(1,1,2,2);
    Eigen::Matrix2f subMat1 = mat.block<2,2>(1,1);
    //block()函数=>block(startRow,startCol,blockRows,blockCols)
    //和数据操作一样，从0起始，这里就是(1,1)开始，取2行2列的子矩阵
    std::cout<<"Sub matrix:\n"<<subMat<<std::endl;
    std::cout<<"Sub1 matrix:\n"<<subMat1<<std::endl;

    return 0;
}