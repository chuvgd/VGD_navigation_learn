# Eigen库的基本使用教程

## 安装Eigen库

相比于其他库，Eigen 的特殊之处在于，它是一个纯用头文件搭建起来的库（这非常神奇！），这意
味着你只能找到它的头文件，而没有.so 或.a 那样的二进制文件

这里的平台是ubuntu22.04，直接使用

```shell
sudo apt install libeigen3-dev 
```

这里简单介绍一下相关后缀：

- libxxx：只会安装libxxx.so.x.x的动态库
- libxxx-dev(develope)：包含了库的接口(.h文件)和静态库以及动态库，如果编译需要用到该库，那么需要安装dev版本（一般都是安装dev版本）

- libxxx-dbg(debug)：包含调试符号，通常仅供开发人员使用
- libxxx-utils(utility)：通常提供一些额外的命令行工具

## 概述和核心特征

它专为高效的[线性代数运算](https://zhida.zhihu.com/search?content_id=255865596&content_type=Article&match_order=1&q=线性代数运算&zd_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJ6aGlkYV9zZXJ2ZXIiLCJleHAiOjE3ODk5MTg0MTksInEiOiLnur_mgKfku6PmlbDov5DnrpciLCJ6aGlkYV9zb3VyY2UiOiJlbnRpdHkiLCJjb250ZW50X2lkIjoyNTU4NjU1OTYsImNvbnRlbnRfdHlwZSI6IkFydGljbGUiLCJtYXRjaF9vcmRlciI6MSwiemRfdG9rZW4iOm51bGx9.ZELaarhTujZwQHzlRf009lJn7mI5yrbVSUkWAVjVUPc&zhida_source=entity)、矩阵运算以及[数值解法](https://zhida.zhihu.com/search?content_id=255865596&content_type=Article&match_order=1&q=数值解法&zd_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJ6aGlkYV9zZXJ2ZXIiLCJleHAiOjE3ODk5MTg0MTksInEiOiLmlbDlgLzop6Pms5UiLCJ6aGlkYV9zb3VyY2UiOiJlbnRpdHkiLCJjb250ZW50X2lkIjoyNTU4NjU1OTYsImNvbnRlbnRfdHlwZSI6IkFydGljbGUiLCJtYXRjaF9vcmRlciI6MSwiemRfdG9rZW4iOm51bGx9.qLpzF7zu6CCsp0r82dF3bij2zvfKfN8zolShj97cECQ&zhida_source=entity)等任务而设计，是处理矩阵和[向量运算](https://zhida.zhihu.com/search?content_id=255865596&content_type=Article&match_order=1&q=向量运算&zd_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJ6aGlkYV9zZXJ2ZXIiLCJleHAiOjE3ODk5MTg0MTksInEiOiLlkJHph4_ov5DnrpciLCJ6aGlkYV9zb3VyY2UiOiJlbnRpdHkiLCJjb250ZW50X2lkIjoyNTU4NjU1OTYsImNvbnRlbnRfdHlwZSI6IkFydGljbGUiLCJtYXRjaF9vcmRlciI6MSwiemRfdG9rZW4iOm51bGx9.tv86KnR05ngnnmYkm0pemRrMN_4bjFN9BiEwF1Lcptg&zhida_source=entity)的得力工具

Eigen支持多种矩阵类型，其命名：d——double，f——float，i——int，c——复数

Matrix2f就是表示一个2*2元素均为float类型的矩阵

数值运算：矩阵加减乘除，求逆，特征值分解等高效线性代数运算

重点：计算高效，相较于传统方法计算求解起来更加高效

## 基础语法

### 头文件模块解析

- Core：提供矩阵和向量的基本操作，如矩阵的加减乘除，转置等，是基础模块
- Geometry：支持2d和3d的向量变换，旋转矩阵和四元数等几何领域，适用于计算机图形学和机器人学
- Sparse：专注于稀疏矩阵的存储和运算，优化了稀疏矩阵的处理效率，处理大规模的稀疏矩阵非常有效

### 矩阵模板类分析

核心类：Matrix

```cpp
Matrix<
    typename Scalar, 
    int RowsAtCompileTime, 
    int ColsAtCompileTime, 
    int Options = 0, 
    int MaxRowsAtCompileTime = RowsAtCompileTime, 
    int MaxColsAtCompileTime = ColsAtCompileTime>
```

- typename Scalar：指定矩阵元素的数据类型，如float，double等
- int RowsAtCompileTime：编译时确定的矩阵行数
- int ColsAtCompileTime：列数
- int Options：默认值为0，一般无需更改
- int MaxRowsAtCompileTime：最大行数，若提前知道矩阵行数的极限，可进行设置，默认与RowsAtCompileTime相同
- int MaxColsAtCompileTime：最大列数，默认与ColsAtCompileTime相同

在内存对齐方面，Eigen会根据不同的平台和编译器进行优化，以提高内存的访问效率

在使用时，一般无需手动干预，但是在某些特殊情况下，可能需要注意内存对齐的问题，以免性能下降

## 矩阵运算核心功能实现

### 创建与初始化方法

在Eigen库中，矩阵的创建与初始化方法有很多，逗号初始化是一种简介直观的方法，适用于较小的矩阵

block()函数：

- 固定大小

```cpp
block<blockRows,blockCols>(startRow,startCol)
//行数和列数都是模板参数，编译器常量（编译器已知）
```

- 动态大小

```cpp
block(startRow,startCol,blockRows,blockCols)
//行数和列数都是运行期参数（普通函数参数）
```

### 算术运算与线性代数

矩阵的四则运算有一定限制，矩阵加法和减法要求两个矩阵的行数化和列数必须相同

矩阵乘法要求第一个矩阵的列等于第二个矩阵行数，逐元素乘除是对应元素之间的运算，而矩阵乘法是按照线性代数的规则进行的

逆矩阵，行列式和迹的计算在Eigen库中也很方便

- inverse()函数进行逆矩阵的计算
- determinant()函数进行行列式的计算
- trace()函数进行迹的计算

### 矩阵分解和求解器

Eigen库提供了多种矩阵分解方法：如LU，QR和SVD分解

- LU：求解线性方程组
- QR：最小二乘法
- SVD：在数据降维和矩阵近似等方面有广泛应用

注意：

```
在进行矩阵分解和求解线性方程组的时候，要注意数值稳定性问题
当矩阵接近奇异，计算结果可能有较大误差
可以通过检查矩阵的条件数来判断矩阵的病态程度，条件数越大，矩阵越病态
```

## 核心：Eigen库计算位姿变换

- 旋转矩阵（3*3）：Eigen::Matrix3d
- 旋转向量（3*1）：Eigen::AngleAxisd
- 四元数（4*1）：Eigen::Quaterniond
- 平移矩阵（3*1）：Eigen::Vector3d
- 变换矩阵（4*4）：Eigen::Isometry3d

这里都是弧度制（double）

### 1. 旋转向量

旋转角为alpha(顺时针)，旋转轴为(x,y,z)

初始化：

```cpp
Eigen::AngleAxisd rotation_vector(alpha,Vector3d(x,y,z));
Eigen::AngleAxisd yawAngele(alpha,Vector3d::UnitZ());
```

旋转向量转旋转矩阵:

```cpp
Eigen::Matrix3d rotation_matrix;
rotation_matrix = rotation_vector.matrix();

rotation_matrix = rotation_vector.toRotationMatrix();
```

旋转向量转欧拉角：

```cpp
Eigen::Vector3d eulerAngle = rotation_vector.matrix().eulerAngles(0,1,2);
```

旋转向量转四元数：

```cpp
Eigen::Quaterniond quaternion(rotation_vector);

Eigen::Quaterniond quaternion;
quaternion = rotation_vector;
```

### 2.旋转矩阵

初始化：

```cpp
Eigen::Matrix3d rotation_matrix;
rotation_matrix<<x_00,x_01,x_02,x_10,x_11,x_12,x_20,x_21,x_22;
```

旋转矩阵转旋转向量：

```cpp
Eigen::AngleAxisd rotation_vector(ratation_matrix);
Eigen::AngleAxisd rotation_vector;
rotation_vector = ratation_matrix;

Eigen::AngleAxisd rotation_vector;
rotation_vector.fromRotationMatrix(rotation_matrix);
```

旋转矩阵转欧拉角：

```cpp
Eigen::Vector3d eulerAngle = rotation_matrix.eulerAngles(0,1,2);
```

旋转矩阵转四元数：

```cpp
Eigen::Quaterniond quaternion(rotation_matrix);

Eigen::Quaterniond quaternion;
quaternion = rotation_matrix;
```

### 3. 欧拉角（主要看怎么进行实现）

初始化：

```cpp
Eigen::Vector3d eulerAngele(roll,pitch,yaw);
```

欧拉角转旋转向量：

```cpp
Eigen::AngleAxisd rollAngle(AngleAxisd(eulerAngle(0),Vector3d::UnitX()));
Eigen::AngleAxisd pitchAngle(AngleAxisd(eulerAngle(1),Vector3d::UnitY)));
Eigen::AngleAxisd yawAngle(AngleAxisd(eulerAngle(2),Vector3d::UnitZ()));
//这里可以看到是按照世界坐标系相关转轴进行旋转的，属于外旋

Eigen::AngleAxisd rotation_vector;
rotation_vector = yawAngle*pitchAngle*rollAngle;
```

欧拉角转旋转矩阵：

```cpp
Eigen::AngleAxisd rollAngle(AngleAxisd(eulerAngle(0),Vector3d::UnitX()));
Eigen::AngleAxisd pitchAngle(AngleAxisd(eulerAngle(1),Vector3d::UnitY)));
Eigen::AngleAxisd yawAngle(AngleAxisd(eulerAngle(2),Vector3d::UnitZ()));

Eigen::Matix3d rotation_matrix;
rotation_matrix = yawAngle*pitchAngle*rollAngle;
```

欧拉角转四元数

```cpp
Eigen::AngleAxisd rollAngle(AngleAxisd(eulerAngle(0),Vector3d::UnitX()));
Eigen::AngleAxisd pitchAngle(AngleAxisd(eulerAngle(1),Vector3d::UnitY)));
Eigen::AngleAxisd yawAngle(AngleAxisd(eulerAngle(2),Vector3d::UnitZ()));

Eigen::Quaterniond quaternion;
quaternion=yawAngle*pitchAngle*rollAngle;
```

## 四元数

初始化：
```cpp
Eigen::Quaterniond quaternion(w,x,y,z);
```

四元数转旋转向量：

```cpp
Eigen::AngleAxisd rotation_vector(quaternion);

Eigen::AngleAxisd rotation_vector = quaternion;
```

四元数转旋转矩阵：

```cpp
Eigen::Matix3d rotation_matrix.matrix();

Eigen::Matix3d rotation_matrix.toRotationMatrix();
```

四元数转欧拉角：

```cpp
Eigen::Vector3d eulerAngle = quaternion.matrix().eulerAngles(0,1,2);
//转旋转矩阵之后转欧拉角
//按照xyz/rpy
```

