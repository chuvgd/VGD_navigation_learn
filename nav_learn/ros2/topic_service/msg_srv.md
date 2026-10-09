# 自定义msg和srv

先来强调一下ROS2相关项目包含顺序

```
创建工作空间->在工作空间下创建功能包->进行整理和构建编译
```

为什么需要创建工作空间，然后进行把有相关功能的功能包整合整理到一起进行构建编译，在本篇就能看出

首先讲解一下有关自定义msg和srv的知识

## 如何创建自定义的msg和srv

首先在同一个工作空间下，这里是```topic_service```工作空间下创建对应的功能包

这里不赘述相关流程

首先在创建的包下```tutorial_interfaces```创建```msg```和```srv```目录

在```msg```目录下创建```Num.msg```，```Sphere.msg```

```msg
int64 num
```

```msg
geometry_msgs/Point center
float64 radius
```

在```srv```目录下```AddThreeInts.srv```

```srv
int64 a
int64 b
int64 c
---
int64 sum
```

由于在msg中用了```geometry_msgs```相关依赖

在```CMakeLists.txt```中

```cmake
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Num.msg"
  "msg/Sphere.msg"
  "srv/AddThreeInts.srv"
  DEPENDENCIES geometry_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
)
#这里rosidl_generate_interfaces中第一个参数必须是包名称开始{PROJECT_NAME}
```

在```package.xml```中

由于接口依赖生成特定语言的代码，所以需要**声明**构建工具的依赖项```rosidl_default_generators```，```rosidl_default_runtime```是运行时或者执行阶段(runtime)的依赖项，```rosidl_interface_packages```是接口所需要的，```geometry_msgs```是包的依赖

**在package.xml必须进行声明**，这里不进行原因阐述，只是当作工具去运用

```xml
<depend>geometry_msgs</depend>
<buildtool_depend>rosidl_default_generators</buildtool_depend>
<exec_depend>rosidl_default_runtime</exec_depend>
<member_of_group>rosidl_interface_packages</member_of_group>
```

构建完毕，就可以用相关命令行以及在当前工作空间下其他的功能包中进行包含相关消息类型并进行项目的构建

这里：为什么一定是同一工作空间下而不能跨工作空间进行，个人看了很多博客以及ai并结合对cmake的理解，认为

像在工作空间下进行```colcon build```命令，会在工作空间的目录下生成```/build``` ```/install``` ```/log```

三个目录，如果在同一ws下，我们会发现创建的自定义接口有cmake的相关配置文件生成在```/install```目录下，对于在同ws下的其他功能包需要使用我们自定义的消息包时，利用```find_package()```命令就可以找到相关自定义消息包进行构建，反之跨工作空间就是不行的

```
因而，在未来进行大型项目的构建时，我更建议不要把所有的功能包放在同一个ws下，而是类似于
ws->小ws->同功能的各种功能包
就是在ws下再创建各种小ws目录把各种同功能的功能包放进这个小ws中
最后进行colcon build在大ws和小ws均可，只要管理好相关依赖和路径，更推荐在大ws下构建，因为依赖相关的问题在ros2中过于玄学，在ai时代肯定会把大家的工作空间搞得乌烟瘴气，不如直接在大ws下直接交给colcon build进行统一构建——主要是为了find_package()名旅客
```





