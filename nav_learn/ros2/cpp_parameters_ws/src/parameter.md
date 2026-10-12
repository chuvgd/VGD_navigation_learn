# PARAMETER

这里依旧只对相关的代码进行解释，有关参数通信方面的API进行解释

```cpp
class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    this->declare_parameter("my_parameter", "world");

    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalParam::timer_callback, this));
  }
```

这里还是构造函数然后继承```rclcpp::Node```

构造函数第一行创建了一个名为```my_parameter```的参数，其默认值为```world```，参数类型是从默认值推导出来的，这里是字符串类型

```cpp
//这里就是参数：
my_parameter : world
```

构造函数还创建了定时器进行发布，周期是1000ms，定时器会定时回调```timer_callback```函数

这里来看一下```timer_callback```函数

```cpp
void timer_callback()
{
  std::string my_param = this->get_parameter("my_parameter").as_string();

  RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

  std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
  this->set_parameters(all_new_parameters);
}
```

函数第一行从节点中获取参数```my_parameter```，并进行存储在```my_param```中

```cpp
std::string my_param = this -> get_parameter("my_parameter").as_string();
```

并进行日志打印

最后用```set_parameters```函数将```my_parameter```设置回默认值```world```，保证用户在外部改变了参数，也能确保总是能被重置回原始值

```cpp
std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parame("my_parameter","world")};
this -> set_parameters(all_new_parameters);
```

最后是```timer_```声明

```cpp
private:
	rclcpp::TimerBase::SharedPtr timer_;
```

```main```函数也是创建类（节点）实例，并进行```rclcpp::spin(node)```来处理节点数据

这里总结一下：

```cpp
declare_parameter("my_parameter","world");
//参数声明函数，主要是声明这个函数并进行默认值初始化，参数类型由默认值自动推导
get_parameter("my_parameter");
//一般是获取参数的值进行变量存储并使用
set_parameters(std::vector<rclcpp::Parameter> new_parameter = {rclcpp::Parameter("my_parameter","vgd")});
//这个是设置参数的值，如果参数没有默认值，可使用set函数的设置的参数值，用于批量设置参数值
std::vector<rclcpp::Parameter> new_parameter = {rclcpp::Parameter("my_parameter","vgd"),rclcpp::Parameter("your_parameter","rm")}
set_parameter(new_parameter);
//等价于
ros2 param set /<节点名> my_parameter vgd;
ros2 param set /<节点名> your_parameter rm;
```

参数通信：其实就是一种基于服务的通信，因为我们可以请求对声明的参数进行修改

```shell
ros2 param list
```

我们可以看到自定义参数```my_parameter```

```shell
ros2 param set /minimal_param_node my_parameter earth
```

设置成功后会输出```Set parameter successful```，表示服务端设置成功，返回响应

这里设置自定义参数并请求重新set就是一种服务通信，请求并响应

set是客户端请求改变参数，最后服务端进行修改最后返回响应

```cpp
class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    param_desc.description = "This parameter is mine!";

    this->declare_parameter("my_parameter", "world", param_desc);

    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalParam::timer_callback, this));
  }
```

这里是为参数添加描述：可以为参数设置对应的描述

```cpp
auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
param_desc.description = "This parameter is mine!";
```

最后通过

```shell
ros2 param describe /minimal_param_node my_parameter
```

来查看类型和描述