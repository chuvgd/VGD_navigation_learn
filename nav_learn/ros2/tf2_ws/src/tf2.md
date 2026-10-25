# TF树

## 编写静态广播器

静态变换的发布一般用于机器人底盘与传感器或者非运动部位之间的关系

这里我们既可以通过编写代码，通过静态发布器进行相关的发布；也可以直接用相关的命令行进行

下面还是直接对代码进行相关的解释

```cpp
#include <memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class StaticFramePublisher : public rclcpp::Node
{
public:
  explicit StaticFramePublisher(char * transformation[])
  : Node("static_turtle_tf2_broadcaster")
  {
    tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

    // Publish static transforms once at startup
    this->make_transforms(transformation);
  }

private:
  void make_transforms(char * transformation[])
  {
    geometry_msgs::msg::TransformStamped t;

    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = transformation[1];

    t.transform.translation.x = atof(transformation[2]);
    t.transform.translation.y = atof(transformation[3]);
    t.transform.translation.z = atof(transformation[4]);
    tf2::Quaternion q;
    q.setRPY(
      atof(transformation[5]),
      atof(transformation[6]),
      atof(transformation[7]));
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    tf_static_broadcaster_->sendTransform(t);
  }

  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
};

int main(int argc, char * argv[])
{
  auto logger = rclcpp::get_logger("logger");

  // Obtain parameters from command line arguments
  if (argc != 8) {
    RCLCPP_INFO(
      logger, "Invalid number of parameters\nusage: "
      "$ ros2 run learning_tf2_cpp static_turtle_tf2_broadcaster "
      "child_frame_name x y z roll pitch yaw");
    return 1;
  }

  // As the parent frame of the transform is `world`, it is
  // necessary to check that the frame name passed is different
  if (strcmp(argv[1], "world") == 0) {
    RCLCPP_INFO(logger, "Your static turtle name cannot be 'world'");
    return 1;
  }

  // Pass parameters and initialize node
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StaticFramePublisher>(argv));
  rclcpp::shutdown();
  return 0;
}
```

首先头文件部分：

```cpp
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
```

```cpp
#include "geometry_msgs/msg/transform_stamped.hpp"
```

这个头文件是我们包含访问消息类型，并将其发布到转换树中

```cpp
#include "rclcpp/rclcpp.hpp"
```

这个是我们需要继承的节点基类```rclcpp::Node```

```cpp
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
```

```tf::Quaternion```是四元数类，提供方便的成员函数，将欧拉角转换为四元数，反之也是

同时还包含使用```tf2_ros/static_transform_broadcaster.h```，使静态发布变得简单

对于源文件：

```cpp
class StaticFramePublisher : public rclcpp::Node
{
public:
  explicit StaticFramePublisher(char * transformation[])
  : Node("static_turtle_tf2_broadcaster")
  {
    tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

    // Publish static transforms once at startup
    this->make_transforms(transformation);
  }
```

构造函数部分需要传入字符串指针，并将传入的字符串指针传入```make_transforms```函数进行初始化；同时我们创建了一个对象，这个对象是我们填充后发送的消息

具体看一下发布消息的相关逻辑：

```cpp
void make_transforms(char* transfromation[]){
            geometry_msgs::msg::TransformStamped t;

            t.header.stamp = this->get_clock()->now();
            t.header.frame_id = "world";
            t.child_frame_id = transfromation[1];

            t.transform.translation.x = atof(transfromation[2]);
            t.transform.translation.y = atof(transfromation[3]);
            t.transform.translation.z = atof(transfromation[4]);
            tf2::Quaternion q;
            q.setRPY(
                atof(transfromation[5]),
                atof(transfromation[6]),
                atof(transfromation[7])
            );
            t.transform.rotation.x = q.x();
            t.transform.rotation.y = q.y();
            t.transform.rotation.z = q.z();
            t.transform.rotation.w = q.w();

            tf_static_broadcaster_ -> sendTransform(t);
        }
```

对于坐标转换发布器而言，也是一种话题发布机制，需要发布相关的消息类型

，同时坐标转换的广播器也是发布者，具有自己的发布者话题类型

在这个函数中，我们首先接收相关的字符串数组，然后对相关的消息类型（```geometry_msgs::msg::TransformStamped``` ）的消息进行填充

发布一个从```frame_id```to```child_frame_id```的坐标变换，同时我们需要给发布的变换一个时间戳，用当前事件进行标记

```cpp
t.header.stamp = this->get_clock()->now();
t.header.frame_id = "world";
t.child_frame_id = transformation[1];
```

同时，填充乌龟的位置姿态（平移和旋转）

```cpp
t.transform.translation.x = atof(transformation[2]);
t.transform.translation.y = atof(transformation[3]);
t.transform.translation.z = atof(transformation[4]);
tf2::Quaternion q;
q.setRPY(
  atof(transformation[5]),
  atof(transformation[6]),
  atof(transformation[7]));
t.transform.rotation.x = q.x();
t.transform.rotation.y = q.y();
t.transform.rotation.z = q.z();
t.transform.rotation.w = q.w();
```

最后，用创建的广播器进行静态发布

```cpp
tf_static_broadcaster_->sendTransform(t);
```



最后对节点进行运行：

```cpp
ros2 run learning_tf2_cpp static_turtle_tf2_broadcaster mystaticturtle 0 0 1 0 0 0
```

这里是和主函数传入参数有关

```cpp
int(int argc,char** argv)
```

```argv```第一个参数一般是可执行文件名称，后面开始就是和程序相关进行交互，具体不进行赘述

同时，对于静态发布器，官方教程更推荐用专门工具链进行完成，利用```tf2_ros```包下的```static_transform_publisher```可执行文件进行执行

注意：静态发布器的类型是```tf2_ros::StaticTransformBroadcaster```

```shell
ros2 run tf2_ros static_transfrom_publisher --x x --y y --z z --yaw yaw --pitch pitch --roll roll --frame_id frame_id --child-frame-id child_frame_id
```

这个命令行发布一个静态坐标变换，使用x/y/z偏移（米）和偏航/俯仰/滚转（弧度）

```shell
ros2 run tf2_ros static_transfrom_publisher --x x --y y --z z --qx qx --qy qy --qz qz --qw qw --frame-id frame_id --child-frame-id child_frame_id
```

这个命令行也是发布一个静态坐标变换，使用四元数进行发布

同样地，可以使用```launch```进行可执行文件的发布

```python
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
             package='tf2_ros',
             executable='static_transform_publisher',
             arguments = ['--x', '0', '--y', '0', '--z', '1', '--yaw', '0', '--pitch', '0', '--roll', '0', '--frame-id', 'world', '--child-frame-id', 'mystaticturtle']
        ),
    ])
```

对于```--frame-id```和```--child-frame-id```是必须进行参数写入，其他均为可选



## 编写动态广播器

很多时候其实有关坐标变化是不断进行改变的，需要通过实时话题进行订阅然后发布动态广播器，这里进行相关代码讲解

```cpp
#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"

class FramePublisher : public rclcpp::Node
{
public:
  FramePublisher()
  : Node("turtle_tf2_frame_publisher")
  {
    // Declare and acquire `turtlename` parameter
    turtlename_ = this->declare_parameter<std::string>("turtlename", "turtle");

    // Initialize the transform broadcaster
    tf_broadcaster_ =
      std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    // Subscribe to a turtle{1}{2}/pose topic and call handle_turtle_pose
    // callback function on each message
    std::ostringstream stream;
    stream << "/" << turtlename_.c_str() << "/pose";
    std::string topic_name = stream.str();

    subscription_ = this->create_subscription<turtlesim::msg::Pose>(
      topic_name, 10,
      std::bind(&FramePublisher::handle_turtle_pose, this, std::placeholders::_1));
  }

private:
  void handle_turtle_pose(const std::shared_ptr<turtlesim::msg::Pose> msg)
  {
    geometry_msgs::msg::TransformStamped t;

    // Read message content and assign it to
    // corresponding tf variables
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = turtlename_.c_str();

    // Turtle only exists in 2D, thus we get x and y translation
    // coordinates from the message and set the z coordinate to 0
    t.transform.translation.x = msg->x;
    t.transform.translation.y = msg->y;
    t.transform.translation.z = 0.0;

    // For the same reason, turtle can only rotate around one axis
    // and this why we set rotation in x and y to 0 and obtain
    // rotation in z axis from the message
    tf2::Quaternion q;
    q.setRPY(0, 0, msg->theta);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    tf_broadcaster_->sendTransform(t);
  }

  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  std::string turtlename_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FramePublisher>());
  rclcpp::shutdown();
  return 0;
}
```

头文件部分：

```cpp
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"
```

这里是对```turtlesim/msg/Pose```进行话题订阅，然后用动态广播器进行tf的发布，所以需要相关的头文件

对于参数变量部分，需要对相关参数进行声明并给默认值

这里是对```turtlename```参数进行声明和赋值默认值

然后设置相关的参数变量```turtlename_```

```cpp
turtlename_ = this->declare_parameter<std::string>("turtlename", "turtle");
std::string turtlename_;
```

接着来看相关构造函数部分的逻辑

```cpp
FramePublisher():Node("tf2_frame_publisher"){
            //declare and acquire parameter
            turtlename_ = this -> declare_parameter<std::string>("turtlename","turtle");

            tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

            //Subscribe to turtle {1}{2}/pose topic and call handle_turtle_pose
            //callback function on each message
            std::ostringstream stream;
            stream<<"/"<<turtlename_.c_str()<<"/pose";
            std::string topic_name = stream.str();

            subscription_ = this->create_subscription<turtlesim::msg::Pose>(topic_name,10,
                std::bind(&FramePublisher::handle_turtle_pose,this,std::placeholders::_1));
        }
```

在构造函数中，首先对父类构造函数进行初始化，然后对声明```topic_name```进行相关的赋值和初始化，后续在订阅者部分对话题进行订阅并执行相关的回调函数，这里还是强调回调函数本身的参数是```ros2```中订阅者函数需要传入的参数类型而定的，这里不过多赘述

这里订阅```/turtle/pose```并执行相关回调函数，这个回调函数就是动态广播器发布相关```tf```

这里我们看下相关具体的回调函数逻辑

```cpp
void handle_turtle_pose(const std::shared_ptr<turtlesim::msg::Pose> msg){
            geometry_msgs::msg::TransformStamped t;

            t.header.stamp = this -> get_clock()->now();
            t.header.frame_id = "world";
            t.child_frame_id = turtlename_.c_str();

            t.transform.translation.x = msg->x;
            t.transform.translation.y = msg->y;
            t.transform.translation.z = 0.0;

            tf2::Quaternion q;
            q.setRPY(0,0,msg->theta);
            t.transform.rotation.x = q.x();
            t.transform.rotation.y = q.y();
            t.transform.rotation.z = q.z();
            t.transform.rotation.w = q.w();

            tf_broadcaster_ -> sendTransform(t);
        }
```

回调函数中传入的参数是订阅的消息，同时广播器需要广播特定话题的消息

```cpp
geometry_msgs::msg::TransformStamped t;
```

tf的结构需要相关的时间戳，```frame_id```和具体的坐标变换段

这里就是从```world```到```turtle```的坐标变换

同时位置姿态传入相关的话题消息，最后利用动态发布器进行发布

```cpp
tf_broadcaster_ -> sendTransform(t);
```



## 编写监听器

tf2监听器就是获取已经存在的坐标变换，通过监听器我们可以更为灵活地进行其他的坐标变换

这里还是只是对相关代码进行逻辑上解释

头文件部分：

```cpp
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "turtlesim/srv/spawn.hpp"
```

这里我们需要重点关注的是

```cpp
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
```

这是监听坐标变换的关键

同时代码实现中还用到了服务通信相关内容，这里不再进行赘述

源文件部分：

先看构造函数

```cpp
class FrameListener : public rclcpp::Node{
    public:
        FrameListener():Node("turtle_tf2_frame_listener"),turtle_spawning_service_ready_(false),turtle_spawned_(false){
            //declare and acquire 'target_frame' parameter
            target_frame_ = this -> declare_parameter<std::string>("target_frame","turtle1");

            tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this -> get_clock());

            //定义监听器对turtle1 to turtle2
            tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

            //create a client to spawn a turtle
            spawner_ = this -> create_client<turtlesim::srv::Spawn>("spawn");

            //create a client to a spawn a turtle
            publisher_ = this -> create_publisher<geometry_msgs::msg::Twist>("turtle2/cmd_vel",1);

            //call on_timer function every second
            //创建定时器，每1s执行一次回调函数
            timer_ = this -> create_wall_timer(1s,std::bind(&FrameListener::on_timer,this));
        }
```

在构造函数中是本次函数需要执行的完整逻辑，先对父类构造函数进行相关的初始化，然后对成员变量进行初始化，这里是将成员变量赋值为```false```

函数中，我们先对参数变量进行声明和初始化，```target_frame```为```turtle1```

在监听器中，```buffer```和```listener```经常一起进行使用

我们需要创建缓冲区对象

```cpp
tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this -> get_clock());
//其构造函数是要传入相关的时间戳
```

创建监听区对象，并将缓冲区相关内容进行传递

```cpp
tf_listener_ =
  std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
//构造函数中指定了所需要传递的参数
```

一旦监听器被创建，会开始通过线路接收tf2变换，并对这些变换进行缓冲，时间一般是10s

同时我们创建了相关的客户端和发布者，这里不进行这些逻辑上的讲解，只关注相关的监听器

在定时器回调函数中我们创建了需要监听的两个坐标系位置

```cpp
std::string fromFrameRel = target_frame_.c_str();
std::string toFrameRel = "turtle2";
```

调用```lookupTransform```方法进行查询相关坐标变化

注意：```lookupTransform```方法是```geometry_msgs::msg::TransformStamped```数据类型，传入的参数是```目标坐标系``` ```源坐标系``` ```转换的时间```

这里就是从```turtle1```转换到```turtle2```坐标系，同时```tf2::TimePointZero```代表在缓冲区中最新可用的坐标变换（这个涉及到时间戳相关，需要进一步后续内容的学习）

```cpp
t = tf_buffer_->lookupTransform(
  toFrameRel, fromFrameRel,
  tf2::TimePointZero);
```

