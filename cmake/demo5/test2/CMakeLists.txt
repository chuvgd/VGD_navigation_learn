cmake_minimum_required(VERSION 3.15)
project(test2)

aux_source_directory(./ SRC)
#注意：子目录定义的变量名不能直接给主目录的CMakeLists.txt使用
#但是主目录的CMakeLists.txt里面的变量可以给子目录使用
include_directories(${HEADPATH})
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})
link_directories(${LIBPATH})
link_libraries(${SORTLIB})
add_executable(${APPNAME2} ${SRC})

install(TARGETS ${APPNAME2} DESTINATION ${INSTALL_BIN_DIR})