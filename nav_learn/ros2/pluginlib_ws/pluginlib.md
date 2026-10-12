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

```cpp
#include "polygon_plugins/polygon_plugins.hpp"
#include <polygon_base/regular_polygon.hpp>
#include <cmath>

namespace polygon_plugins
{
  class Square : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        side_length_ = side_length;
      }

      double area() override
      {
        return side_length_ * side_length_;
      }

    protected:
      double side_length_;
  };

  class Triangle : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        side_length_ = side_length;
      }

      double area() override
      {
        return 0.5 * side_length_ * getHeight();
      }

      double getHeight()
      {
        return sqrt((side_length_ * side_length_) - ((side_length_ / 2) * (side_length_ / 2)));
      }

    protected:
      double side_length_;
  };
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(polygon_plugins::Square, polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Triangle, polygon_base::RegularPolygon)
```

这里来先讲解头文件部分：```#include <polygon_base/regular_polygon.hpp>```

对于这个跨包的头文件引入，是靠着导出机制和```find_package()```联动完成

通过之前定义抽象类的包下CMake中的：

```cmake
ament_export_include_directories(
  include
)
```

导出头文件目录，在```install```目录下会生成```install/polygon_base/share/polygon_base/cmake/ament_cmake_export_include_directories-extras.cmake```这样的cmake配置文件

```find_package()```会对```polygon_base```的cmake配置文件进行查找，相当于是找第三方库的方式，找到后利用```ament_target_dependencies()```可以进行一系列的头文件路径包含等添加依赖的操作

源文件部分就是重写```initialize```函数先对成员变量进行初始化然后计算面积

重写```initialize``` ```area```等函数

最后用了一个比较神奇的头文件将类注册为插件

```cpp
#include <pluginlib/class_list_macros.hpp>
```

```cpp
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Square, polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Triangle, polygon_base::RegularPolygon)
```

用了```PLUGINLIB_EXPORT_CLASS```宏，插件类的类型：```polygon_plugins::Square``` ```polygon_plugins::Triangle```；以及基类类型：```polygon_base::RegularPolygon```

插件注册完毕之后，我们需要对插件进行序列化（描述），以方便我们后续进行调用，**为了给插件加载器对插件进行加载并调用**

在pkg目录下创建一个xml文件进行序列化

```xml
<library path="polygon_plugins">
  <class type="polygon_plugins::Square" base_class_type="polygon_base::RegularPolygon">
    <description>This is a square plugin.</description>
  </class>
  <class type="polygon_plugins::Triangle" base_class_type="polygon_base::RegularPolygon">
    <description>This is a triangle plugin.</description>
  </class>
</library>
```

讲解一下：

- 首先是```<library path>```  ```</library>```标签导出插件库的相对路径，即```install/polygon_plugins/lib/libpolygon_plugins.so```
- ```<class type>``` ```</class>```标签说明了我们插件的相关类型，这里就是```namespace::class_name```
- ```<base_class_type>```标签说明了我们自定义插件的抽象基类，即说明插件的接口
- ```description```对插件的描述

最后在CMake中对插件进行导出

```cmake
pluginlib_export_plugin_description_file(polygon_base plugins.xml)
```

- 参数1：继承的接口（抽象类）的包```polygon_base```
- 参数2：插件声明xml的相对路径```plugins.xml```

插件注册完毕和导出后，在后续的ros代码中就可以进行动态加载并使用

```cpp
#include <pluginlib/class_loader.hpp>
#include <polygon_base/regular_polygon.hpp>

int main(int argc, char** argv)
{
  // To avoid unused parameter warnings
  (void) argc;
  (void) argv;

  pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("polygon_base", "polygon_base::RegularPolygon");

  try
  {
    std::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createSharedInstance("polygon_plugins::Triangle");
    triangle->initialize(10.0);

    std::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createSharedInstance("polygon_plugins::Square");
    square->initialize(10.0);

    printf("Triangle area: %.2f\n", triangle->area());
    printf("Square area: %.2f\n", square->area());
  }
  catch(pluginlib::PluginlibException& ex)
  {
    printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
  }

  return 0;
}
```

这里需要理解的关键：头文件中的```<pluginlib/class_loader.hpp>```

- 模板基类作为接口，需要加载插件时对```pluginlib::ClassLoader<polygon_base::RegularPolygon>```模板类进行实例化
- 实例化构造函数传入参数是：
  - 参数1为基类包名的字符串，即```"polygon_base"```
  - 参数2是插件基类的名称（插件基类接口类型）的字符串：```"polygon_base::RegularPolygon"```

当需要使用具体插件时，就可以使用创建的插件基类接口的成员函数```createSharedInstance```进行对具体插件的初始化和使用

这里是通过共享指针进行管理：

```cpp
std::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createSharedInstance("polygon_plugins::Triangle");
```

这个成员函数需要传入的参数是```const std::string & lookup_name```

即具体插件类型的字符串类型```"polygon_plugins::Triangle"```

注意：插件将动态加载，因为插件已经被注册到了```pluginlib```中，无需声明具体定义的插件类的依赖

这里我们通过硬编码的插件名实例化插件类（构造函数传入插件名），但是也可以动态地通过参数进行实现，具体可以参考nav2各种规划器，控制器等实现