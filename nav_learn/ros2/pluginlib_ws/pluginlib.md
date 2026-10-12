# Pluginlib

```pluginlib```是用于在ros包中加载和卸载插件的cpp库

插件是可以动态加载的类，从运行时库（共享对象，动态链接库）加载出来

使用```pluginlib```，不用显式地将应用与包含类的库关联，而是可以在任何时刻打开包含导出类的库，而无需应用程序事先知道该库或者包含类定义的头文件

插件机制更多用于扩展员和修改应用行为

这里讲解一下代码相关内容——首先是抽象基类给插件提供一个接口

```cpp
#ifndef POLYGON_BASE_REGULAR_POLYGON_HPP
#define POLYGON_BASE_REGULAR_POLYGON_HPP

namespace polygon_base
{
  class RegularPolygon
  {
    public:
      virtual void initialize(double side_length) = 0;
      virtual double area() = 0;
      virtual ~RegularPolygon(){}

    protected:
      RegularPolygon(){}
  };
}  // namespace polygon_base

#endif  // POLYGON_BASE_REGULAR_POLYGON_HPP
```

这个就是抽象基类，因为由纯虚函数的定义，必须显式定义子类继承抽象基类对成员方法进行重写

```cmake
install(
  DIRECTORY include/
  DESTINATION include
)
```

需要将头文件路径安装到```install```目录下

同时：导出安装的头文件路径

```cmake
ament_export_include_directories(
  include
)
```

现在来对抽象类的成员方法进行具体实现

