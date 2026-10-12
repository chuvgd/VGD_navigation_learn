# Topic通信

此处不做知识点的总结和讲解，只解释代码相关语法内容

## 头文件部分(发布者)

```cpp
#include "rclcpp/rclcpp.hpp"
//此处是ros2系统最基本最常用的部分
#include "std_msg/msg/string.hpp"
//ros2话题通信内置消息类型，类似于结构体
```

## 源文件部分(发布者)

```cpp
class MinimalPublisher : public rclcpp::Node
```

继承rclcpp::Node类创建了节点类MinimalPublisher，这里的每个this指针都指向这个节点

```cpp
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(
    500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }
```

构造函数部分重点注意：首先是初始化列表，由于继承过来的Node类是有参构造函数，所以初始化列表需要先对父类构造函数传入参数，同时将成员变量count_初始化为0

```cpp
explicit rclcpp::Node::Node(const std::string &node_name, const rclcpp::NodeOptions &options = rclcpp::NodeOptions())
```

这里我们看一下Node类构造函数要传入的参数，一定要传入的参数是```std::string```类型的```node_name```，由于是const类型，直接写```Node("node_name")```也不会报错，若是非const引用，则会出现报错，非const引用不能绑定右值

回到构造函数函数主体：

- 发布者使用```create_publisher```函数初始化，消息类型是```std_msgs::msg::String```，topic名是```topic```，队列大小是10,用于限制备份时消息数量
- timer_让timer_callback函数每s执行2次

这些成员函数都是Node父类节点继承而来，相关API要传入的参数具体可以调转

```cpp
private:
        rclcpp::TimerBase::SharedPtr timer_;
        //共享指针对象，std::shared_ptr<rclcpp::TimerBase>
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        //using rclcpp::Publisher<std_msgs::msg::String>::SharedPtr = std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> 
        //模板类rclcpp::Publisher<std_msgs::msg::String>的一个智能指针对像
        size_t count_;

        void timer_callback(){
            auto message = std_msgs::msg::String();
            message.data = "Hello world!"+std::to_string(count_++);
            RCLCPP_INFO(this->get_logger(),"Publishing:'%s'",message.data.c_str());
            publisher_->publish(message);
        }
```

这里定义了```timer_callback```函数，设置消息数据并实际发布消息的函数，```RCLCPP_INFO```确保每个消息都打印到控制台

同时声明定时器，发布者和计数变量，否则会出现上述public中报红

同时```timer_callback```函数中也无法将消息发布出去

**注意：ros2中用了很多typedef去别名变量类型**

```cpp
using rclcpp::Publisher<std_msgs::msg::String>::SharedPtr = std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> 
using rclcpp::TimerBase::SharedPtr = std::shared_ptr<rclcpp::TimerBase> 
```

main函数中，我们需要执行这个节点，首先需要对ros2操作系统进行初始化，```rclcpp::init```，然后用```rclcpp::spin```处理节点数据，其实就是实例化类之后，调用其否构造函数，由于构造函数中创建了发布者并执行了定时器，定时器中传入了函数指针进行回调，因而可以看到每秒2次输出INFO日志

```cpp
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
```

## 头文件部分(订阅者)

```cpp
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
```

对于订阅者部分，由于话题发布和订阅需要话题消息类型一致，所以头文件部分用到了```std_msgs/msg/string.hpp```

## 源文件部分(订阅者)

构造函数部分：

```cpp
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }
```

发布者和订阅者的topic名和消息类型必须匹配才能进行通信，这里构造函数也是一样的和发布者，先初始化父类的构造函数，再去进行构造函数内部逻辑

调用创建订阅者的成员函数进行创建，对于创建订阅者的模板成员函数，需要传入的基本参数：

- ```const std::string &topic_name```
-  ```const rclcpp::QoS &qos```
- ```std::_Bind<...> &&callback```：这里传入回调函数(函数指针)

回调函数：

```cpp
private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
```

回调函数传入的参数是和发布者消息类型一致的msg参数，这里是拿左值引用传入，减少拷贝且不能在函数内部**只可读msg变量**

main函数部分和发布者一样，不再作过多讲解
