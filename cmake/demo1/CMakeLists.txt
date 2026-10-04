cmake_minimum_required(VERSION 3.15)

project(test)

set(SRC add.cpp div.cpp main.cpp mult.cpp sub.cpp)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# set(EXECUTABLE_OUTPUT_PATH ./src)
#指定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 11)
add_executable(app ${SRC})
