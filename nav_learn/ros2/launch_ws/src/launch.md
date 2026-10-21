# ROS2_LAUNCH

## 创建启动文件

背景：ros2中启动系统负责帮助用户描述其系统的配置，然后按描述执行，系统配置包括

运行哪些程序，在哪里运行，传递哪些参数，以及ros特定的约定，通过为每个组件提供不同的配置，可以方便地在整个系统中重复使用组件，同时还能负责监控已经启动进程地状态，并对这些进程的状态变做出报告和反应

这里主要讲述用```python```进行launch文件的编写

这里举个例子

```python
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            namespace='turtlesim1',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='turtlesim',
            namespace='turtlesim2',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='turtlesim',
            executable='mimic',
            name='mimic',
            remappings=[
                ('/input/pose', '/turtlesim1/turtle1/pose'),
                ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
            ]
        )
    ])
```

这里我们解释一下相关内容，上面的启动文件启动了由```turtlesim```包的三个节点组成的系统，这个系统的目标是启动两个```turtlesim```窗口，使一个```turtle```模仿另一个的```turtle```的移动

启动这两个```turtlesim```节点之间唯一的区别是它们的命名空间不同

专有的命名空间可以启动两个节点，无需考虑到节点名称或者```topic```名称冲突

同时通过专有的命名空间可以区分不同```turtlesim```设计的消息

在最后一个节点中我们对相关话题进行了重映射，```mimic```的```/input/pose```话题被重映射到```/turtlesim1/turtle1/pose```，同理```/output/cmd_vel```也是被重映射到```/turtlesim2/turtle1/cmd_vel```

这里来分开进行解释

```python
from launch import LaunchDescription
from launch_ros.actions import Node
```

这些```import```语句引入一些```launch```模块

```python
def generate_launch_description():
   return LaunchDescription([

   ])
```

这里是对启动配置的描述

```python
Node(
    package='turtlesim',
    namespace='turtlesim1',
    executable='turtlesim_node',
    name='sim'
),
Node(
    package='turtlesim',
    namespace='turtlesim2',
    executable='turtlesim_node',
    name='sim'
),
```

这里是对两个```Node```节点启动的描述

```py
Node(
    package='turtlesim',
    executable='mimic',
    name='mimic',
    remappings=[
      ('/input/pose', '/turtlesim1/turtle1/pose'),
      ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
    ]
)
```

最后是启动了```mimic```节点，并进行了重映射

对于含有```launch```文件的包，最好在包的```package.xml```文件中添加一个```exec_depend```依赖项，声明依赖于```ros2launch```包

```xml
<exec_depend>ros2launch</exec_depend>
```

这使得构建包后，```ros2 launch```命令确定是可用的，而且还确保了所有的```launch```文件格式均能够被识别到



## 使用可替换变量

启动文件用于启动节点，服务和运行进程，这些操作可能需要参数，这些参数会影它们的行为，可替换变量（```substitutions```）可以用于参数，以提供更大的灵活性，描述可重用的启动文件

可替换变量是只在启动文件执行期间才会计算的变量，可以用于获取特定信息，如启动配置，环境变量或者计算一些```py```表达式

注意：最后确保安装文件能正确安装

```cmake
install(DIRECTORY
        launch
        DESTINATION share/${PROJECT_NAME}/
)
```

这里的例子是创建一个可以调用并传递参数给另一个启动文件的启动文件

这里我们详细进行讲述

```python
from launch_ros.substitutions import FindPackageShare

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution, TextSubstitution


def generate_launch_description():
    colors = {
        'background_r': '200'
    }

    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                PathJoinSubstitution([
                    FindPackageShare('launch_tutorial'),
                    'launch',
                    'example_substitutions.launch.py'
                ])
            ]),
            launch_arguments={
                'turtlesim_ns': 'turtlesim2',
                'use_provided_red': 'True',
                'new_background_r': TextSubstitution(text=str(colors['background_r']))
            }.items()
        )
    ])
```

先来看相关头文件

```python
from launch_ros.substitutions import FindPackageShare

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution, TextSubstitution
```

```FindPackageShare```用于查找```launch_tutorial```包路径，使用```PathJoinSubstitution```将找到的包路径与```example_substitutions.launch.py```的文件名连接起来

```python
PathJoinSubstitution([
    FindPackageShare('launch_tutorial'),
    'launch',
    'example_substitutions.launch.py'
])
```

```launch_arguments```中用于参数的传递

同时在同一个文件夹中创建一个带有可替换变量的启动文件

```python
from launch_ros.actions import Node

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, TimerAction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression


def generate_launch_description():
    turtlesim_ns = LaunchConfiguration('turtlesim_ns')
    use_provided_red = LaunchConfiguration('use_provided_red')
    new_background_r = LaunchConfiguration('new_background_r')

    turtlesim_ns_launch_arg = DeclareLaunchArgument(
        'turtlesim_ns',
        default_value='turtlesim1'
    )
    use_provided_red_launch_arg = DeclareLaunchArgument(
        'use_provided_red',
        default_value='False'
    )
    new_background_r_launch_arg = DeclareLaunchArgument(
        'new_background_r',
        default_value='200'
    )

    turtlesim_node = Node(
        package='turtlesim',
        namespace=turtlesim_ns,
        executable='turtlesim_node',
        name='sim'
    )
    spawn_turtle = ExecuteProcess(
        cmd=[[
            'ros2 service call ',
            turtlesim_ns,
            '/spawn ',
            'turtlesim/srv/Spawn ',
            '"{x: 2, y: 2, theta: 0.2}"'
        ]],
        shell=True
    )
    change_background_r = ExecuteProcess(
        cmd=[[
            'ros2 param set ',
            turtlesim_ns,
            '/sim background_r ',
            '120'
        ]],
        shell=True
    )
    change_background_r_conditioned = ExecuteProcess(
        condition=IfCondition(
            PythonExpression([
                new_background_r,
                ' == 200',
                ' and ',
                use_provided_red
            ])
        ),
        cmd=[[
            'ros2 param set ',
            turtlesim_ns,
            '/sim background_r ',
            new_background_r
        ]],
        shell=True
    )

    return LaunchDescription([
        turtlesim_ns_launch_arg,
        use_provided_red_launch_arg,
        new_background_r_launch_arg,
        turtlesim_node,
        spawn_turtle,
        change_background_r,
        TimerAction(
            period=2.0,
            actions=[change_background_r_conditioned],
        )
    ])
```

先定义一些启动配置变量```LaunchConfiguration```，这些变量用于存储启动参数的值，并将它们传递给所需要的```action```，可以在启动描述```LaunchDescription```的任何部分获取启动参数的值

同时```DeclareLaunchArgument```用于定义可以从上面的启动文件或者控制台传递进来的启动参数

```python
turtlesim_ns = LaunchConfiguration('turtlesim_ns')
use_provided_red = LaunchConfiguration('use_provided_red')
new_background_r = LaunchConfiguration('new_background_r')
#配置并定义相关的参数变量

turtlesim_ns_launch_arg = DeclareLaunchArgument(
    'turtlesim_ns',
    default_value='turtlesim1'
)
use_provided_red_launch_arg = DeclareLaunchArgument(
    'use_provided_red',
    default_value='False'
)
new_background_r_launch_arg = DeclareLaunchArgument(
    'new_background_r',
    default_value='200'
)
#初始化（默认值）
```

定义相关节点，同时```namespace```设置为用```LaunchConfiguration```产生的```turtlesim_ns```

```cpp
turtlesim_node = Node(
    package='turtlesim',
    namespace=turtlesim_ns,
    executable='turtlesim_node',
    name='sim'
)
```

然后，定义一个名为```spawn_turtle```的```action```，```ExecuteProcess```带有相应的```cmd```参数，这个命令会调用```turtlesim```节点的```spawn```服务

同样也用到了之前定义的参数变量

```python
spawn_turtle = ExecuteProcess(
    cmd=[[
        'ros2 service call ',
        turtlesim_ns,
        '/spawn ',
        'turtlesim/srv/Spawn ',
        '"{x: 2, y: 2, theta: 0.2}"'
    ]],
    shell=True
)
```

同样的方法用于```change_background_r```和```change_background_r_conditioned```两个 ```action```，注意：在```change_background_r_conditioned```这个只有在提供的```new_background_r```参数等于200且```use_provided_red```设置为```true```才会执行

构建完成后，利用相关的命令行进行传递参数和启动```launch```文件

```shell
ros2 launch launch_tutorial example_substitutions.launch.py turtlesim_ns:='turtlesim3' use_provided_red:='True' new_background_r:=200
```

