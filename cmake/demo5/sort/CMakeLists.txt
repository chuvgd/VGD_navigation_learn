cmake_minimum_required(VERSION 3.15)
project(sort)

aux_source_directory(./ SRC)
#注意：子目录定义的变量名不能直接给主目录的CMakeLists.txt使用
#但是主目录的CMakeLists.txt里面的变量可以给子目录使用
include_directories(${HEADPATH})
#静态库要指定 ARCHIVE_OUTPUT_DIRECTORY（LIBRARY_* 只对动态库生效），且必须在 add_library 之前设置
set(LIBRARY_OUTPUT_DIRECTORY ${LIBPATH})
add_library(${SORTLIB} STATIC ${SRC})