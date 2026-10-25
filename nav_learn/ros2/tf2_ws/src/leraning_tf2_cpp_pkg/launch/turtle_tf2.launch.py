from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='leraning_tf2_cpp_pkg',
            executable='tf2_broadcaster',
            name='broadcaster1',
            parameters=[
                {'turtlename':'turtle1'}
            ]
        ),
        DeclareLaunchArgument(
            'target_frame',default_value='turtle1',
            description='Target frame name.'
        ),
        Node(
                    package='leraning_tf2_cpp_pkg',
                    executable='tf2_broadcaster',
                    name='broadcaster1',
                    parameters=[
                        {'turtlename':'turtle2'}
                    ]
                ),
        Node(
            package='leraning_tf2_cpp_pkg',
            executable='tf2_listener',
            name='listener',
            parameters=[
                {
                    'target_frames':LaunchConfiguration('target_frame')
                }
            ]
        ),
    ])