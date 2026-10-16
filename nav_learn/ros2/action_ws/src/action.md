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

**对于服务器部分：**

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

这俩参数是```create_server```这个模板函数本身决定的，这里来看一下相关的```defination```

```cpp
template<typename ActionT, typename NodeT>
typename Server<ActionT>::SharedPtr
create_server(
  NodeT node,
  const std::string & name,
  typename Server<ActionT>::GoalCallback handle_goal,
  typename Server<ActionT>::CancelCallback handle_cancel,
  typename Server<ActionT>::AcceptedCallback handle_accepted,
  const rcl_action_server_options_t & options = rcl_action_server_get_default_options(),
  rclcpp::CallbackGroup::SharedPtr group = nullptr)
{
  return create_server<ActionT>(
    node->get_node_base_interface(),
    node->get_node_clock_interface(),
    node->get_node_logging_interface(),
    node->get_node_waitables_interface(),
    name,
    handle_goal,
    handle_cancel,
    handle_accepted,
    options,
    group);
}
```

对于```create_server```这个函数是在```rclcpp_action```的```namespace```下一个模板函数，这个模板函数参数类型是```ActionT```和```NodeT```，在要传入的参数方面，我们重点介绍三个函数指针（回调函数）

```cpp
typename Server<ActionT>::GoalCallback handle_goal,
typename Server<ActionT>::CancelCallback handle_cancel,
typename Server<ActionT>::AcceptedCallback handle_accepted,
```

这里需要注意：用到了```typename```的关键字的一个重要作用——模板参数类型依赖，由于模板参数类型为```ActionT```，而具体回调函数的类型是```Server<ActionT>::GoalCallback```，依赖于```ActionT```，必须要```typename```声明相关依赖

```cpp
using GoalCallback = std::function<GoalResponse(
        const GoalUUID &, std::shared_ptr<const typename ActionT::Goal>)>
```

```typename Server<ActionT>::GoalCallback handle_goal```这个类型的函数实际上是一个函数包装器，返回的是一个可调用函数对象（函数指针），函数类型是```rclcpp_action::GoalResponse```，而函数形式参数是```const GoalUUID &```和```std::shared_ptr<const typename ActionT::Goal>```，我们实际写相关回调函数逻辑时也需要按照此标准进行

回到处理目标的回调函数，在这个函数中通过传入相关消息接口的消息后直接返回枚举类型```GoalResponse```下```ACCEPT_AND_EXECUTE```的变量值，表示直接接受所有的目标

```cpp
rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleFibonacci> goal_handle){
                RCLCPP_INFO(this -> get_logger(),"Received request to cancel goal");
                (void)goal_handle;
                return rclcpp_action::CancelResponse::ACCEPT;
            }
```

对于处理取消目标的回调函数，也是按照上述相关标准进行的参数进行传入，不再进行赘述

目前这个实现只告诉客户端它接受了取消请求

```cpp
void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    using namespace std::placeholders;
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&FibonacciActionServer::execute, this, _1), goal_handle}.detach();
  }
```

最后一个回调函数用于接受一个新的目标并开始处理

由于执行一个长时间运行的操作，我们创建一个线程来执行实际的工作，并快速从```handle_accepted```返回

```
// this needs to return quickly to avoid blocking the executor, so spin up a new thread
```

后面进一步的处理和更新都在新线程的```execute```方法中完成

```cpp
void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(1);
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<Fibonacci::Feedback>();
    auto & sequence = feedback->partial_sequence;
    sequence.push_back(0);
    sequence.push_back(1);
    auto result = std::make_shared<Fibonacci::Result>();

    for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i) {
      // Check if there is a cancel request
      if (goal_handle->is_canceling()) {
        result->sequence = sequence;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
      }
      // Update sequence
      sequence.push_back(sequence[i] + sequence[i - 1]);
      // Publish feedback
      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(this->get_logger(), "Publish feedback");

      loop_rate.sleep();
    }

    // Check if goal is done
    if (rclcpp::ok()) {
      result->sequence = sequence;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
  }
```

对于这个工作线程每秒处理一个斐波那契数列的序列号，为每一步发布一个反馈更新，当处理完成时，将```goal_handle```标记为成功，并退出

**对于客户端部分：**

首先是创建```rclcpp::Node```的子类

```cpp
class FibonacciActionClient : public rclcpp::Node
```

构造函数具体逻辑方面：

```cpp
explicit FibonacciActionClient(const rclcpp::NodeOptions & options)
  : Node("fibonacci_action_client", options)
  {
    this->client_ptr_ = rclcpp_action::create_client<Fibonacci>(
      this,
      "fibonacci");

    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&FibonacciActionClient::send_goal, this));
  }
```

父类节点先进行初始化构造，在构造函数内部逻辑中

```cpp
this->client_ptr_ = rclcpp_action::create_client<Fibonacci>(
      this,
      "fibonacci");
```

 实例化一个新的动作通信客户端 ，需要传入三个参数

- ```action```类型名称：```Fibonacci```
- 一个```action```所属节点：```this```
- ```action```名称：```"fibonacci"```

注意：客户端和服务端的名称需要相同

同时实例化定时器去周期性地发送客户端的目标

```cpp
this->timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
std::bind(&FibonacciActionClient::send_goal, this));
```

每当触发定时器逻辑时，即每500ms都会调用相关的回调函数```send_goal```

```cpp
void send_goal()
  {
    using namespace std::placeholders;

    this->timer_->cancel();

    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = Fibonacci::Goal();
    goal_msg.order = 10;

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&FibonacciActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&FibonacciActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&FibonacciActionClient::result_callback, this, _1);
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
  }
```

这个函数主要做了以下的事情：

- 取消定时器（这样它只会被调用一次）
- 等待```action```服务器启动
- 实例化一个新的```Fibonacci::Goal```
- 设置响应，反馈以及结果的回调（注意：这里的回调函数的参数都是由具体模板函数/类需要传入参数而确定的）
- 发送目标到服务器

当服务器接收并接受目标时，它会向客户端返回一个响应，这个响应由```goal_response_callback```处理

```cpp
void goal_response_callback(const GoalHandleFibonacci::SharedPtr & goal_handle)
  {
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }
```

假设服务器接收了目标，就会进行处理，所有回到客户端的反馈都由```feedback_callback```处理

```cpp
void feedback_callback(
    GoalHandleFibonacci::SharedPtr,
    const std::shared_ptr<const Fibonacci::Feedback> feedback)
  {
    std::stringstream ss;
    ss << "Next number in sequence received: ";
    for (auto number : feedback->partial_sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  }
```

服务器处理完毕后，会向客户端返回一个结果，这个结果由```result_callback```处理

```cpp
void result_callback(const GoalHandleFibonacci::WrappedResult & result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }
    std::stringstream ss;
    ss << "Result received: ";
    for (auto number : result.result->sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
    rclcpp::shutdown();
  }
};  // class FibonacciActionClient
```



