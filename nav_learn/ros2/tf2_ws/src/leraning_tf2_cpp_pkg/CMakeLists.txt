cmake_minimum_required(VERSION 3.8)
project(leraning_tf2_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(static_broadcaster_publisher src/static_broadcaster.cpp)
add_executable(tf2_broadcaster src/tf2_broadcaster.cpp)
add_executable(tf2_listener src/tf2_listener.cpp)
ament_target_dependencies(
  static_broadcaster_publisher
  geometry_msgs
  rclcpp
  tf2
  tf2_ros
)
ament_target_dependencies(
  tf2_broadcaster
  geometry_msgs
  turtlesim
  rclcpp
  tf2
  tf2_ros
)
ament_target_dependencies(
  tf2_listener
  geometry_msgs
  turtlesim
  rclcpp
  tf2
  tf2_ros
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
        static_broadcaster_publisher
        tf2_broadcaster
        tf2_listener
        DESTINATION
        lib/${PROJECT_NAME}
        )
install(DIRECTORY
        launch
        DESTINATION
        share/${PROJECT_NAME}/
        )

ament_package()
