# 读懂ROS2中的CMakeLists.txt

在ros2中，有专门的ament_cmake对原版cmake进行优化，但是本人看不出优化在哪里，其实还是有点过于繁琐，但是看ros2大型项目时，我们不可避免的就是先对cmake文件和launch文件进行入手，所以在此文本中总结一下在ros2常用常见的ament_cmake用法

## 一. 一个功能包的诞生

使用```ros2 pkg creat <package_name>```可以生成一个功能包框架

我们可以看到这样一个文件tree

![](/home/ubuntu/VGD_navigation/nav_learn/ros2/cmake_ros2/assets/ament_cmake.png)

一个功能包的构建消息将会包含在```CMakeLists.txt```和```package.xml```这两个文件中

- ```package.xml```：文件中包含该功能包的依赖信息，可以帮助编译工具```colcon```确定多个功能包编译顺序，当我们需要单独编译功能包时必须保证编译的包名和```package.xml```文件中的一致

- ```CMakeLists.txt```：这个则告诉我们是如何构建功能包的

```shell
colcon build --packages-select <package_name>
```

## 二. 详细分析CMakeLists.txt

这里看到知乎up上是对```nav2_costmap_2d```这个功能包的```CMakLists.txt```进行的分析

```cmake
cmake_minium_required(VERSION 3.5)
project(nav2_costmap_2d)
```

**注意：project名称必须和package.xml中的名称保持一致**

```cmake
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(laser_geometry REQUIRED)
find_package(map_msgs REQUIRED)
find_package(message_filters REQUIRED)
find_package(nav2_common REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(nav2_util REQUIRED)
find_package(nav2_voxel_grid REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(rmw REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(angles REQUIRED)
```

这个是查找系统中的依赖项，即查找第三方库进行代码的构建

```cmake
find_package(Eigen3 REQUIRED)
include_directories(
	include
	${EIGEN3_INCLUDE_DIRS}
)
```

这个是对于普通的cmake，这里就是将Eigen3库在系统中进行寻找，然后把当前目录下的include目录包含进来，然后将eigen3库设置的变量```EIGEN3_INCLUDE_DIRS```（eigen3库相关头文件目录）进行解析然后包含进来

对于ros2来说不必这么麻烦

一步步来看

```cmake
add_library(nav2_costmap_2d_core SHARED
  src/array_parser.cpp
  src/costmap_2d.cpp
  src/layer.cpp
  src/layered_costmap.cpp
  src/costmap_2d_ros.cpp
  src/costmap_2d_publisher.cpp
  src/costmap_math.cpp
  src/footprint.cpp
  src/costmap_layer.cpp
  src/observation_buffer.cpp
  src/clear_costmap_service.cpp
  src/footprint_collision_checker.cpp
  src/costmap_collision_checker.cpp
  src/costmap_collision_checker_ros.cpp
  plugins/costmap_filters/costmap_filter.cpp
)
```

这个其实和普通cmake一致，将各种源文件进行编译链接成库文件```nav2_costmap_2d_core```，注意这里是共享库文件

对于构建这个库文件，我们还需要有相关依赖，这就是和上述```find_package```一起配合使用，首先先设置变量

```cmake
set(dependencies
  geometry_msgs
  laser_geometry
  map_msgs
  message_filters
  nav2_msgs
  nav2_util
  nav2_voxel_grid
  nav_msgs
  pluginlib
  rclcpp
  rclcpp_lifecycle
  sensor_msgs
  std_msgs
  tf2
  tf2_geometry_msgs
  tf2_ros
  tf2_sensor_msgs
  visualization_msgs
  angles
)
```

其实已经看出些许端倪，普通cmake不会这样去设置变量的，而在ros2中为什么这么设置，当然是为了引出后面的```ament_target_dependencies```

```cmake
ament_target_dependencies(nav2_costmap_2d_core
  ${dependencies}
)
```

```ament_target_dependencies```：是官方推荐的添加依赖项，它使得依赖项的库，头文件和自身的依赖项被正常找到，通常来说，若依赖项为ROS2的功能包时，则使用```ament_target_dependencies```，若功能包有多个库，将其一并包含

```cmake
target_link_libraries(nav2_costmap_2d_client
  nav2_costmap_2d_core
)
```

这个其实和普通的cmake用法一致，只是将```target：nav2_costmap_2d_client```链接上之前的库文件```nav2_costmap_2d_core```

```cmake
install(TARGETS
  nav2_costmap_2d
  nav2_costmap_2d_markers
  nav2_costmap_2d_cloud
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)
```

安装库的语句，将在```install/nav2_costmap_2d/lib```下安装库文件

这个也属于普通cmake的用法

```cmake
install(TARGETS <target_name>
		DESTINATION <target_destination>
		)
```

这里补充一下：配置安装目录相关关键字

```cmake
install(
	TARGETS Mylib
	LIBRARY DESTINATION lib #动态库安装路径
	ARCHIVE DESTINATION lib #静态库安装路径
	RUNTIME DESTINATION bin #可执行文件安装路径
	PUBLIC_HEADER DESTINATION include #头文件安装路径
)
```

- DESTINATION后面的路径可以自行指定，但是默认的根目录为```CMAKE_INSTALL_PREFIX```，默认值的话，对于UNIX系统：```/usr/local```，WIN下默认值：```c:Program Files/${ROJECT_NAME}```，比如上述如果在linux系统下上述就被安装在了：```/usr/local/lib```

对于ros2来说：

```cmake
install(TARGETS
  nav2_costmap_2d
  nav2_costmap_2d_markers
  nav2_costmap_2d_cloud
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)
```

这里安装的路径就是```install/nav2_costmap_2d/lib/nav2_costmap_2d```

对于ros2而言，安装其他文件或者目录一起配合执行可执行文件是很常见的，所有要安装其他相关的文件或者目录：比如说launch/yaml等

```cmake
install(FILES costmap_plugins.xml
		DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY include/
		DESTINATION include/
)

install(DIRECTORY include launch params
		DESTINATION share/${PROJECT_NAME}		
)
```

```cmake
ament_export_include_directories(include)
```

这条语句标记该功能包的头文件位置，以便其他功能包要依赖该功能包时能顺利找到对应的头文件

```cmake
ament_export_libraries(layers filters nav2_costmap_2d_core nav2_costmap_2d_client)
```

一个ros2功能包中存在多个库，如果希望其他的功能包能链接到这些库用这个语句去声明这些库

声明好后：
```cmake
find_package(nav2_costmap_2d REQUIRED)

ament_target_dependencies(example_node nav2_costmap_2d)

ament_export_dependencies(${dependencies})
#导出依赖到下游软件包，这是必须的，这样该库的使用者就不必为那些依赖find_package了
```

还有一个导出插件，这个主要导航重写插件用的比较多

```cmake
pluginlib_export_plugin_description_file(nav2_costmap_2d costmap_plugins.xml)
```

导出插件的描述文件以便```pluginlib::classLoader```类去找到相应的插件

最后一定要写：

```cmake
ament_package()
#最后一行写
```

项目安装是通过```ament_package()```完成的，并且每个软件包必须恰好执行一次这个调用，它会安装```package.xml```文件，用```ament```索引注册该软件包，并安装```CMake```的配置（和可能的目标）文件，以便其他软件包可以用```find_package```找到该软件包
