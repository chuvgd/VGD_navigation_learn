from launch_ros.actions import Node

from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument,EmitEvent,ExecuteProcess,LogInfo,RegisterEventHandler,TimerAction)

from launch.conditions import IfCondition
from launch.event_handlers import (OnExecutionComplete,OnProcessExit,OnProcessIO,OnProcessStart,OnShutdown)

from launch.events import Shutdown
from launch.substitutions import (EnvironmentVariable,FindExecutable,LaunchConfiguration,LocalSubstitution,PythonExpression)

def generate_launch_description():
    turtlesim_ns = LaunchConfiguration('turtlesim_ns')
    use_provide_red = LaunchConfiguration('use_provide_red')
    new_background_r = LaunchConfiguration('new_background_r')

    turtlesim_ns_launch_arg = DeclareLaunchArgument(
        'turtlesim_ns',
        default_value='turtlesim1',
    )

    use_provide_red_launch_arg = DeclareLaunchArgument(
        'use_provide_red',
        default_value='False',
    )
    new_background_r_launch_arg = DeclareLaunchArgument(
        'new_background_r',
        default_value='200',
    )

    turtlesim_node = Node(
        package='turtlesim',
        namespace=turtlesim_ns,
        executable='turtlesim_node',
        name='sim',
    )
    spawn_turtle = ExecuteProcess(
        cmd=[[
            'ros2 service call ',
            turtlesim_ns,
            '/spawn ',
            'turtlesim/srv/Spawn ',
            '"{x: 2.0, y: 2.0, theta: 0.2}"'
        ]],
        shell=True
    )
    change_background_r = ExecuteProcess(
        cmd=[[
            FindExecutable(name='ros2'),
            ' param set ',
            turtlesim_ns,
            '/sim background_r ',
            '120'
        ]],
        shell=True 
    )
    change_background_r_condition = ExecuteProcess(
        condition = IfCondition(
            PythonExpression([
                new_background_r,
                ' == 200',
                ' and ',
                use_provide_red,
            ])
        ),
        cmd=[[
            FindExecutable(name='ros2'),
            ' param set ',
            turtlesim_ns,
            '/sim background_r ',
            new_background_r
        ]],
        shell=True
    )

    return LaunchDescription([
        turtlesim_ns_launch_arg,
        use_provide_red_launch_arg,
        new_background_r_launch_arg,
        turtlesim_node,
        RegisterEventHandler(
            OnProcessStart(
                target_action=turtlesim_node,
                on_start=[
                    LogInfo(msg=['Turtlesim started, spawning turtle.']),
                    spawn_turtle,
                ]
            )
        ),
        RegisterEventHandler(
            OnProcessIO(
                target_action=turtlesim_node,
                on_stdout=lambda event: LogInfo(msg='Spawn request says "{}"'.format(event.text.decode().strip()))
            )
        ),
        RegisterEventHandler(
            OnExecutionComplete(
                target_action=spawn_turtle,
                on_completion=[
                    LogInfo(msg=['Spawn completed.']),
                    change_background_r,
                    TimerAction(
                        period=2.0,
                        actions=[change_background_r_condition]
                    )
                ]
            )
        ),
        RegisterEventHandler(
            OnProcessExit(
                target_action=turtlesim_node,
                on_exit=[
                    LogInfo(msg=[EnvironmentVariable(name='USER'),' closed the turtlesim window.']),
                    EmitEvent(event=Shutdown(reason='Window exited.'))
                ]
            )
        ),
        RegisterEventHandler(
            OnShutdown(
                on_shutdown=[LogInfo(
                    msg=['Launch was asked to shutdown:',
                         LocalSubstitution('event.reason')]
                )]
            )
        ),
    ])