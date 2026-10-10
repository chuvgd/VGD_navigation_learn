# 接口(Interfaces)

ROS通常用以下三种类型的接口进行通信:```topics```，```services```，```actions```，ROS2使用一种简化的描述语言，接口定义语言（IDL）来描述这些接口

- msg：.msg——主要用于话题通信
- srv：.srv——描述一个服务，由请求(request)和响应(response)组成
- action：.action——描述动作，由目标(goal)，结果(result)和反馈(feedback)组成

## 消息(msg)

消息是ROS2节点在网络上向其他ROS节点发送数据的一种方式，**不需要有响应**

```.msg```文件分成两个部分组成：字段和常量

- 字段：

```msg
fieldtype1 fieldname1
fieldtype2 fieldname2
fieldtype3 fieldname3
```

- 字段类型：
  - 一种内置类型
  - 一种自定义的消息类型，eg.```geometry_msgs/PoseStamped```

- 字段名称

字段名称必须只由小写字母，数字和下划线组成，它们必须以字母开头，不能以下划线结尾，也不能有两个连续的下划线

- 字段默认值

```msg
fieldtype fieldname fielddefaultvalue
```

```msg
uint8 x 42
int16 y -2000
string full_name "John Doe"
int32[] samples [-200,-100,0,100,200]
```

注意：

```
- string类型的值必须用单引号或者双引号定义
- 目前字符串的值不能被转义
```

- 常量

常量定义就像一个字段描述，只是这个值不能在程序中被改变，这个值的赋值通过```=```来表示

```msg
constanttype CONSTANTNAME = constantvalue
```

```msg
int32 X = 123
int32 Y = -123
string FOO = "foo"
string EXAMPLE = 'bar'
```

注意：

```
常量名必须全部大写
```

## 服务(Service)

服务是一种请求/响应式通信，其中客户端(请求者)等待服务器(响应者)进行简短的计算并返回结果

```service```的描述文件由请求和响应消息类型组成，使用```---```分隔

任何两个使用```---```连接的```.msg```文件都是合法的service描述

```srv
string str
---
string str
```

注意：service不能嵌套在另一个service中

## 动作(Actions)

```actions```是一种长时间运行的请求/响应式通信，其中```action```客户端(请求者)等待```action```服务器(响应者)执行某些操作并返回结果

与服务不同，```action```可以是长时间运行的，在运行中可以提供反馈，并且可以被中断

```action
<request_type> <request_fieldname>
---
<response_type> <response_fieldname>
---
<feeback_type> <feedback_fieldname>
```

请求字段，响应字段和反馈字段都可以是任意数量的

```action
int32 order
---
int32[] sequence
---
int32[] sequence
```

主要是在发送请求中反馈请求和最后给出响应结果

服务器会把目前计算到的序列通过feedback传回给客户端，可以知道相关的进度，同时最后计算完成之后通过response把最后结果返回给客户端

## 在同一个包下使用消息接口

这里和在同一个ws下创建消息接口包然后在```install```下导出相关```cmake```配置文件，然后在其他包下用```find_package()```对自定义消息包进行引入，以包含相关头文件和库文件——就是和引入其他第三方库一样，让其他源文件能够找到第三方库所需要的相关依赖不同

在同一个包下创建消息接口文件目录并创建相关消息接口，然后在src目录下进行使用这个消息接口——但是仅适用简单的功能包，很难做到自定义消息接口的通用性

和在不同功能包下配置自定义消息接口一些不同的地方：

在```CMakeLists.txt```中：

```cmake
find_package(rosidl_default_generators REQUIRED)

#设置变量
set(msg_files
	"msg/AddressBook.msg"
)

rosidl_generate_interfaces(${PROJECET_NAME}
	${msg_files}
)

#确保导出消息运行时依赖项
ament_export_dependencies(rosidl_default_runtime)

add_executable(publish_address_book src/publish_address_book.cpp)
ament_target_dependencies(publish_address_book rclcpp)

#注意：在同一个包下源代码使用自定义消息接口，需要链接相关消息接口
rosidl_get_typesupport_target(cpp_typesupport_target
${PROJECT_NAME} rosidl_typesupport_cpp)
target_link_libraries(publish_address_book "${cpp_typesupport_target}")
#只当作如何使用，不作过多理解相关底层
```

```cmake
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(publish_address_book "${cpp_typesupport_target}")
```

通过这样的操作，目标文件就会找到与```AddressBook.msg```相关的生成的cpp代码，并进行链接

已经可以注意到，当使用来自独立建构的不同包的接口时，这一步是不必要的，只有在想要在定义它们的包中使用接口时（就是同一个包下）才需要这段CMake代码



