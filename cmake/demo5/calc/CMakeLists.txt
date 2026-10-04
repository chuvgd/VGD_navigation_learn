cmake_minimum_required(VERSION 3.15)
project(calc)

aux_source_directory(./ SRC)
#注意：子目录定义的变量名不能直接给主目录的CMakeLists.txt使用
#但是主目录的CMakeLists.txt里面的变量可以给子目录使用
include_directories(${HEADPATH})
set(LIBRARY_OUTPUT_DIRECTORY ${LIBPATH})
add_library(${CALCLIB} STATIC ${SRC})