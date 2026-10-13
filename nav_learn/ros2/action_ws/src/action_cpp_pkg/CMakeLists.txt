cmake_minimum_required(VERSION 3.8)
project(action_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(action_interfaces REQUIRED)

add_library(action_server SHARED src/fibonacci_action_server.cpp)
target_include_directories(action_server PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_definitions(action_server
  PRIVATE "ACTION_TUTORIALS_CPP_BUILDING_DLL")
ament_target_dependencies(action_server
  "action_interfaces"
  "rclcpp"
  "rclcpp_action"
  "rclcpp_components"
)
rclcpp_components_register_node(action_server PLUGIN "action_cpp::FibonaccActionServer" EXECUTABLE fibonacci_action_server)

add_library(action_client SHARED src/fibonacci_action_client.cpp)
target_include_directories(action_client PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_definitions(action_client
  PRIVATE "ACTION_TUTORIALS_CPP_BUILDING_DLL")
ament_target_dependencies(action_client
  "action_interfaces"
  "rclcpp"
  "rclcpp_action"
  "rclcpp_components"
)
rclcpp_components_register_node(action_client PLUGIN "action_cpp::FibonaccActionClient" EXECUTABLE fibonacci_action_client)

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
        action_server
        action_client
        ARCHIVE DESTINATION lib 
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

ament_package()
