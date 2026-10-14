# Action

动作通信是ros2中通信类型之一，主要用于长时间运行的任务

主要是三个部分：目标(goal)，反馈(feedback)和结果(result)

动作通信是两个服务，一个话题组成，功能类似于```service```，但是```action```可以被取消，同时提供稳定的反馈，不同于服务只能返回一个响应

**导航中会经常用到动作通信**

```action client```节点发送一个目标到```action server```节点，客户端确认目标并返回一系列反馈和结果

- 两个服务：
  - 目标服务——客户端请求目标，服务端接收并返回响应；
  - 结果服务——客户端请求目标的结果，服务端不断通过```topic```反馈，最后完成后给出结果的响应
- 一个话题：
  - 反馈话题——服务端给客户端不断反馈话题```feedback```



首先是创建```action```消息接口

在```ws/src```下创建相关功能包，并在```pkg```下创建```action```目录，定义```.action```文件

```action
# Request 请求
---
# Result 结果
---
# Feedback 反馈
```

- 从动作通信的客户端发送到服务端的请求消息，初始化一个新的目标
- 当目标完成时，从服务端发送到客户端的结果消息
- 反馈消息时周期性地从服务器发送到客户端的消息，用于更新目标

这里是一个求解斐波那契数列的消息接口

```action
int32 order
---
int32[] sequence
---
int32[] partial_sequence
```

目标是数列项数```order```，结果是最终算出的数列```sequence```，反馈是目前为止算出的数列```partial_sequence```

同样地，我们需要构建```action```，构建方式和```msg```和```service```有所不同

在```cmake```中：

```cmake
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME} 
	"action/Fibonacci.action"
)
```

在```package.xml```

```xml
<buildtool_depend>rosidl_default_generators</buildtool_depend>

<depend>action_msgs</depend>

<member_of_group>rosidl_interface_packages</member_of_group>
```

这里注意：我们需要依赖于```action_msg```，在```action```中定义依赖了一些额外的元数据



创建完自定义的```action```消息接口后开始创建客户端和服务端

对于服务器部分：

头文件部分

```cpp
#include "action_interfaces/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
```

我们需要包含消息接口的头文件```action_interfaces/action/fibonacci.hpp```，动作通信的```rclcpp_action/rclcpp_action.hpp```

源文件部分

```cpp
class FibonaccActionServer : public rclcpp :: Node
```

一成不变的创建节点基类的子类

```cpp
using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;
```

使用类型别名去简化变量类型，方便后续使用

```cpp
explicit FibonacciActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions()) : Node("fibonacci_action_server", options)
```

构造函数中传入的```const rclcpp::NodeOptions & options = rclcpp::NodeOptions()```参数暂时不作深入研究

在构造函数内部：创建了动作通信的服务器

```cpp
this->action_server_ = rclcpp_action::create_server<Fibonacci>(
      this,
      "fibonacci",
      std::bind(&FibonacciActionServer::handle_goal, this, _1, _2),
      std::bind(&FibonacciActionServer::handle_cancel, this, _1),
      std::bind(&FibonacciActionServer::handle_accepted, this, _1));
```

一个```action```服务器需要6个信息

- ```action```类型的名称：```Fibonacci```

- 动作通信的名称：```"fibonacci"```
- 属于的```ros2```的节点：```this```——属于本节点
- 用于处理目标的回调函数：```handle_goal```
- 用于处理取消的回调函数：```handle_cancel```
- 用于处理目标接受文件的回调函数：```handle_accepted```

在```ros2```中，所有回调函数都要快速返回，否则可能导致```executor```闲置

```cpp
  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const Fibonacci::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received goal request with order %d", goal->order);
    (void)uuid;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }
```

对于目标处理回调函数，传入```const rclcpp_action::GoalUUID & uuid```

和```std::shared_ptr<const Fibonacci::Goal> goal```参数

这俩参数是```create_server```这个模板函数本身决定的，相关解释等明天吧，因为今天要sleep了，不过今天晚上搞清楚了这个也是很值得的，感觉和ros2底层回调executor的理解快接近了(

回到处理目标的回调函数，在这个函数中通过传入相关消息接口的消息后直接返回枚举类型```GoalResponse```下```ACCEPT_AND_EXECUTE```的变量值，表示直接接受所有的目标
