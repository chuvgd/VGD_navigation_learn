cmake_minimum_required(VERSION 3.15)

project(test)

# set(SRC add.cpp div.cpp mult.cpp sub.cpp)
# set(SRC ${PROJECT_SOURCE_DIR}/src)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# set(EXECUTABLE_OUTPUT_PATH ./src)
#指定头文件路径
#这个头文件路径是全局头文件路径，会将这个include下所有的头文件暴露给相关的源文件
#这个会导致出现所有的源文件都去默认包含了${PROJECT_SOURCE_DIR}/include下的头文件，容易造成命名空间或者依赖的污染
# include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 11)
# add_executable(app ${SRC})
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src/library)
# add_library(vgd SHARED ${PROJECT_SOURCE_DIR}/src/add.cpp ${PROJECT_SOURCE_DIR}/src/div.cpp)
# add_library(rm STATIC ${PROJECT_SOURCE_DIR}/src/mult.cpp ${PROJECT_SOURCE_DIR}/src/sub.cpp)
#头文件路径更推荐使用这种方式，只将相关头文件路径暴露给所需要的构建项目中
#PRIVATE：只给库文件包含的相关头文件路径，后续用到的源文件没有包含${PROJECT_SOURCE_DIR}/include
#PUBLIC：会给后续用到的源文件也包含${PROJECT_SOURCE_DIR}/include路径
#INTERFACE：头文件路径不用于库自身的编译，只传递给链接此库的目标
# target_include_directories(vgd PRIVATE ${PROJECT_SOURCE_DIR}/include)
# target_include_directories(rm PRIVATE ${PROJECT_SOURCE_DIR}/include)
# link_libraries(vgd)
add_executable(main main.cpp)
# link_libraries(vgd)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE vgd)
target_link_libraries(main PRIVATE rm)
target_link_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/src/library)
target_link_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/src/library)




