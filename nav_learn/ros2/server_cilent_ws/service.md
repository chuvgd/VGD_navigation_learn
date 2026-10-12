# Service

## 背景

服务是ros2中节点之间的另一种通信方式，基于请求—响应模型，而不是话题发布—订阅模型，服务只在特定时刻被调用时提供数据

通常不建议使用服务进行连续调用，topic或者action更适用

## 头文件部分(服务端)

```cpp
#include "example_interfaces/srv/add_two_ints.hpp"
```

服务消息类型```example_interfaces/srv/AddTwoInts```

通过```ros2 interface show example_interfaces/srv/AddTwoInts```可以看到具体消息类型组成

```cpp
int64 a
int64 b
---
int sum
```

前两行是请求相关定义，横线下是服务回应相关定义

## 源文件部分(服务端)

```cpp
void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
         std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>      response)
{
    response->sum = request->a + request->b;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
        request->a, request->b);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}
```

add函数内部相关逻辑解释：

作为服务端，需要接收到相关请求然后进行服务处理，在add函数中传入```example_interfaces::srv::AddTwoInts::Request```类型的共享指针对象```request```和```example_interfaces::srv::AddTwoInts::Response```类型的共享指针对象```response```，调用相关成员变量进行服务处理，同时打印相关日志

```cpp
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
    node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
```

main函数部分

- 先初始化ros2客户端库——```rclcpp::init(argc, argv);```

- 创建节点

```cpp
auto node = std::make_shared<rclcpp::Node>("add_two_ints_server")
```

这里和之前话题通信不同，话题通信创建了类去继承```rclcpp::Node```父类节点，但是这里由于没有创建类直接创建```rclcpp::Node```基类节点是正确的

- 为该节点创建一个```add_two_ints```服务，自动将其广播到网络，同时为服务添加函数指针作为回调函数

创建服务端函数```create_service```和创建发布者函数传入参数差不多，都是```service_name```，```callback_func```作为主要传入参数

```cpp
rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service = node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints",&add);
```

```cpp
using rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr = std::shared_ptr<rclcpp::Service<example_interfaces::srv::AddTwoInts>>
```

- 运行节点，使服务可用

```cpp
rclcpp::spin(node);
```

## 源文件部分(客户端)

于服务节点类似，创建节点然后创建相关节点客户端

```cpp
std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client =
  node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
```

接下来创建请求，其结构由之前```.srv```文件定义

```cpp
auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
request->a = atoll(argv[1]);
request->b = atoll(argv[2]);
```

这里讲解一下```atoll函数```

```cpp
atoll(const char* str)
//将字符串开头的十进制整数解析为long long类型
```

字符指针数组

```cpp
char* argv[]
```

数组中每个元素的类型都是```char*```，指向的是每个字符串的首地址，其实就是每个元素都是字符串

同时```char* argv[]```与```char** argv```等价，```argv[]```在函数参数中会退化成指针，即```char* argv = char argv[]```

```cpp
char* argv[] = {"hello","world"};
```

- ```argv[0]``` 指向"hello"首个地址(```argv+0```)
- ```argv[1]``` 指向"world"首个地址(```argv+1```)

我们可以看到在ros2的main函数中很多是用```int main(int argc,char* argv[])```

这个是c语言命令行参数，在执行程序时，可以从命令行传值给c语言程序，主要用于外部测试和控制程序，而不是在代码在内对这些值进行硬编码

```cpp
int main(int argc,char** argv);

int main(int argc,char** argv[]);
```

- argc：表示命令行参数，包括程序名本身，因此，argc至少为1
- argv：是一个指向字符串数组的指针，其中每个字符串是一个命令行参数，数组的一个元素(argv[0])通常是程序的名称，接下来的元素是传递给程序的命令行参数

注意：命令行参数之间应该用空格分隔，但是如果参数本身有空格，那么传递参数时候应该把参数放置在""或者''内部

使用场景：

- 配置文件路径
- 模式选择（如调试模式）
- 输入文件和输出文件名
- 运行时选项和标志

注意：

- 命令行参数通常是字符串，如果需要将其转换为数值类型，可以使用标准库函数```atoi```或者```strtol```
- 应该始终验证和处理命令行参数，以防止输入错误或者恶意输入

回到代码本身，while循环给客户端1s时间在网络中搜索服务节点，如果找不到服务节点，它会继续等待

```cpp
while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }
```

这里就是在客户端搜索服务节点到1s时（客户端等待服务端1s）没有找到相关服务节点，会进行```RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...")```，如果这时候客户端被取消，会返回错误日志```RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.")```

如果在这1s找到服务节点，客户端会异步发送请求，然后等待结果

```cpp
auto result = client->async_send_request(request);
```

最后通过一个类似于监测服务节点是否完成进行一个日志打印

```cpp
if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
  }
```
**注意: 和topic一样在服务通信中，也要保证客户端和服务端的名称一致且消息类型一致**