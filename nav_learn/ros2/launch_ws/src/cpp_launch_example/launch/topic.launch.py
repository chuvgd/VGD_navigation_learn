import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='cpp_launch_example',
            executable='publisher_member_function',
            name='publisher_member_function'
        ),
        launch_ros.actions.Node(
            package='cpp_launch_example',
            executable='subscribe_member_function',
            name='subscribe_member_function'
        )
    ])