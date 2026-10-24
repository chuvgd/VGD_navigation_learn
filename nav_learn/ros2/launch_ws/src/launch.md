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



## 使用事件处理器(event handlers)

背景：启动系统是一个执行和管理用户定义进程的系统

负责监视启动的进程的状态，并且报告和响应这些进程状态的变化

这些状态的变化称为事件，可以通过在启动系统值中注册事件处理器(```event handler```)来处理这些事件

事件处理器中可以注册特定事件的处理程序，用于监视进程的状态

详细展开事件处理器机制

```OnProcessStart``` ```OnProcessIO``` ```OnExecutionComplete``` ```OnProcessExit```和```OnShutdown```事件的```RegisterEventHandler```操作在启动描述中已经定义

```python
RegisterEventHandler(
    OnProcessStart(
        target_action=turtlesim_node,
        on_start=[
            LogInfo(msg='Turtlesim started, spawning turtle'),
            spawn_turtle
        ]
    )
),
```

```OnProcessStart```用于注册一个在```turtlesim```节点启动时执行的回调函数

在节点启动时记录一条消息到控制台，并在节点启动时运行```spawn_turtle```的```action```

```python
RegisterEventHandler(
    OnProcessIO(
        target_action=spawn_turtle,
        on_stdout=lambda event: LogInfo(
            msg='Spawn request says "{}"'.format(
                event.text.decode().strip())
        )
    )
),
```

```OnProcessIO```用于注册一个在```spawn_turtle```的```action```向其标准输出写数据时执行的回调函数，它记录了生成请求的结果

```python

RegisterEventHandler(
    OnExecutionComplete(
        target_action=spawn_turtle,
        on_completion=[
            LogInfo(msg='Spawn finished'),
            change_background_r,
            TimerAction(
                period=2.0,
                actions=[change_background_r_conditioned],
            )
        ]
    )
),
```

```OnExecutionComplete```用于注册一个在```spawn_turtle```的```action```完成时的回调函数，记录一条消息到控制台，并在```action```完成时执行```change_background_r```和```change_background_r_conditioned```这俩个```action```

```python
RegisterEventHandler(
    OnProcessExit(
        target_action=turtlesim_node,
        on_exit=[
            LogInfo(msg=(EnvironmentVariable(name='USER'),
                    ' closed the turtlesim window')),
            EmitEvent(event=Shutdown(
                reason='Window closed'))
        ]
    )
),
```

```OnProcessExit```用于注册一个在节点退出时执行```EmitEvent```的```action```来发出一个```Shutdown```事件，当节点窗口关闭，```launch```进程关闭

```python
RegisterEventHandler(
    OnShutdown(
        on_shutdown=[LogInfo(
            msg=['Launch was asked to shutdown: ',
                LocalSubstitution('event.reason')]
        )]
    )
),
```

最后，```OnShutdown```事件处理器用于注册一个回调函数，在启动文件关闭时执行，记录一条消息到控制台，说明关闭启动文件的原因



## 管理大型项目

管理大型项目：**启动多个启动文件，参数，yaml文件，重映射，命名空间，默认参数和Rivz配置**

这里是一个顶层启动文件，启动两个```turtlesim```模拟器，启动TF广播器和监听器，加载参数并启动```Rviz```相关配置

先来介绍顶层文件

顶层文件：启动其他各个模块功能的启动文件，在不同机器人上运行应用时，只需改变顶层文件的参数即可

```python
import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
   turtlesim_world_1 = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/turtlesim_world_1.launch.py'])
      )
   turtlesim_world_2 = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/turtlesim_world_2.launch.py'])
      )
   broadcaster_listener_nodes = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/broadcaster_listener.launch.py']),
      launch_arguments={'target_frame': 'carrot1'}.items(),
      )
   mimic_node = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/mimic.launch.py'])
      )
   fixed_frame_node = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/fixed_broadcaster.launch.py'])
      )
   rviz_node = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/turtlesim_rviz.launch.py'])
      )

   return LaunchDescription([
      turtlesim_world_1,
      turtlesim_world_2,
      broadcaster_listener_nodes,
      mimic_node,
      fixed_frame_node,
      rviz_node
   ])
```

 这个启动文件包含了一系列其他启动文件

启动了两个```turtlesim```模拟器，```tf```广播器，```tf```监听器，模仿器，坐标广播器以及```Rviz```节点

注意：

```
设计提示：顶层启动文件应该比较简短，引用应用中用到的子程序的启动文件，还包含一些顶层常用的启动参数
```

```
设计提示：请注意权衡应用需要多少个顶层启动文件，但是并非所有情况下都是只有一个最顶层的启动文件才是最好的
```

- 参数

  - 在启动文件中设置参数

  ```python
  from launch import LaunchDescription
  from launch.actions import DeclareLaunchArgument
  from launch.substitutions import LaunchConfiguration, TextSubstitution
  
  from launch_ros.actions import Node
  
  
  def generate_launch_description():
     background_r_launch_arg = DeclareLaunchArgument(
        'background_r', default_value=TextSubstitution(text='0')
     )
     background_g_launch_arg = DeclareLaunchArgument(
        'background_g', default_value=TextSubstitution(text='84')
     )
     background_b_launch_arg = DeclareLaunchArgument(
        'background_b', default_value=TextSubstitution(text='122')
     )
  
     return LaunchDescription([
        background_r_launch_arg,
        background_g_launch_arg,
        background_b_launch_arg,
        Node(
           package='turtlesim',
           executable='turtlesim_node',
           name='sim',
           parameters=[{
              'background_r': LaunchConfiguration('background_r'),
              'background_g': LaunchConfiguration('background_g'),
              'background_b': LaunchConfiguration('background_b'),
           }]
        ),
     ])
  ```

  这个启动文件启动了```turtlesim_node```节点，启动了```turtlesim```仿真，并传递了定义和传递节点的仿真配置参数

  - 从```yaml```文件中加载参数

   从```yaml```文件加载参数是一个更为合理且工程化的操作

  ```python
  import os
  
  from ament_index_python.packages import get_package_share_directory
  
  from launch import LaunchDescription
  from launch_ros.actions import Node
  
  
  def generate_launch_description():
     config = os.path.join(
        get_package_share_directory('launch_tutorial'),
        'config',
        'turtlesim.yaml'
        )
  
     return LaunchDescription([
        Node(
           package='turtlesim',
           executable='turtlesim_node',
           namespace='turtlesim2',
           name='sim',
           parameters=[config]
        )
     ])
  ```

  这个启动文件会启动从```yaml```配置文件中加载的参数的```turtlesim_node```，注意这里```yaml```参数文件的路径

  在```yaml```文件中定义参数，可以很容易地存储和加载大量变量

  此外，可以用相关地命令行从```ros2 param```列表中导出```yaml```文件

  这里创建一个名为```turtlesim.yaml```的配置文件，放在包```/config```文件夹中，这个配置文件会被我们启动文件加载

  ```yaml
  /turtlesim2/sim:
     ros__parameters:
        background_b: 255
        background_g: 86
        background_r: 150
  ```

  - 在```yaml```文件中使用通配符

  有时候我们想要在多个节点设置相同的参数，这些节点可能有不同的命名空间或者名称，但是仍然具有相同的参数

  在这种情况下，为不同命名空间和节点名称定义分开的```yaml```文件并不高效

  使用通配符字符，可以在文本值中代替未知字符，以将参数应用于多个不同的节点

  ```yaml
  /**:
     ros__parameters:
        background_b: 255
        background_g: 86
        background_r: 150
  ```

  会给使用这个```yaml```文件的```launch```文件下所有节点设置相关参数

- 命名空间

唯一的命名空间允许系统启动两个相似的节点，而不会出现节点名称或者主题名称冲突

但是如果启动文件包含大量节点，为每个节点定义命名空间会变得比较繁琐，为了解决这个问题，可以使用```PushRosNamespace```动作来为每个启动文件描述定义全局命名空间，这样每个嵌套节点都会自动继承该命名空间

这里举个例子：

```python
from launch.actions import GroupAction
from launch_ros.actions import PushRosNamespace

   ...
   turtlesim_world_2 = IncludeLaunchDescription(
      PythonLaunchDescriptionSource([os.path.join(
         get_package_share_directory('launch_tutorial'), 'launch'),
         '/turtlesim_world_2.launch.py'])
      )
   turtlesim_world_2_with_namespace = GroupAction(
     actions=[
         PushRosNamespace('turtlesim2'),
         turtlesim_world_2,
      ]
   )
```

这里就是为了```turtlesim_world_2.launch.py```启动文件中每个节点都会嵌套上```turtlesim2```命名空间

- 复用节点

```python
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node


def generate_launch_description():
   return LaunchDescription([
      DeclareLaunchArgument(
         'target_frame', default_value='turtle1',
         description='Target frame name.'
      ),
      Node(
         package='turtle_tf2_py',
         executable='turtle_tf2_broadcaster',
         name='broadcaster1',
         parameters=[
            {'turtlename': 'turtle1'}
         ]
      ),
      Node(
         package='turtle_tf2_py',
         executable='turtle_tf2_broadcaster',
         name='broadcaster2',
         parameters=[
            {'turtlename': 'turtle2'}
         ]
      ),
      Node(
         package='turtle_tf2_py',
         executable='turtle_tf2_listener',
         name='listener',
         parameters=[
            {'target_frame': LaunchConfiguration('target_frame')}
         ]
      ),
   ])
```

这个文件中，我们声明了```target_frame```启动参数，并设置了默认值为```turtle```，这个参数值可以进行修改，若没有修改则传递默认值

使用不同的名称和参数启动```turtle_tf2_broadcaster```节点两次，这样可以做到不冲突

同时我们再启动一个```turtle_tf2_listener```节点，并设置```target_frame```参数为前面声明和获取的

- 参数覆盖

在顶层文件中，传递了```target_frame```启动参数

```python
broadcaster_listener_nodes = IncludeLaunchDescription(
   PythonLaunchDescriptionSource([os.path.join(
      get_package_share_directory('launch_tutorial'), 'launch'),
      '/broadcaster_listener.launch.py']),
   launch_arguments={'target_frame': 'carrot1'}.items(),
   )
```

调用了```broadcaster_listener.launch.py```文件并将默认设置的目标坐标系更改为```carrot1```

- 重映射

```python
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
   return LaunchDescription([
      Node(
         package='turtlesim',
         executable='mimic',
         name='mimic',
         remappings=[
            ('/input/pose', '/turtle2/pose'),
            ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
         ]
      )
   ])
```

这个启动文件会启动```mimic```节点，该节点会给一个```turtlesim```发送命令，让其跟随另一个```turtlesim```，这里就是在```/input/pose```话题上接收目标姿态，我们将```/turtle2/pose```话题重映射目标姿态

同时将```/output/cmd_vel```话题重映射到```/turtlesim2/turtle1/cmd_vel```

这样就可以做到在```turtlesim2```中的```turtle1```跟随初始```turtlesim```中的```turtle2```

- 配置文件

```python
import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
   rviz_config = os.path.join(
      get_package_share_directory('turtle_tf2_py'),
      'rviz',
      'turtle_rviz.rviz'
      )

   return LaunchDescription([
      Node(
         package='rviz2',
         executable='rviz2',
         name='rviz2',
         arguments=['-d', rviz_config]
      )
   ])
```

这个启动文件会启动```RViz```，使用```turtle_tf2_py```包中定义的配置文件

- 环境变量

```python
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import EnvironmentVariable, LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
   return LaunchDescription([
      DeclareLaunchArgument(
            'node_prefix',
            default_value=[EnvironmentVariable('USER'), '_'],
            description='prefix for node name'
      ),
      Node(
            package='turtle_tf2_py',
            executable='fixed_frame_tf2_broadcaster',
            name=[LaunchConfiguration('node_prefix'), 'fixed_broadcaster'],
      ),
   ])
```

展示启动文件中调用环境变量，环境变量可以用于定义或者推送命名空间，区分不同计算机或者机器人上的节点

最后在```CMakeLists.txt```中：

```cmake
install(DIRECTORY 
        launch 
        config
        DESTINATION 
        share/${PROJECT_NAME}/
)
```

将```config```和```launch```文件进行安装
