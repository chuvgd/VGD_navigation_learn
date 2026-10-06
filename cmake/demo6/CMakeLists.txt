cmake_minimum_required(VERSION 3.15)
project(test)


set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/install)
set(INSTALL_SHARED_LIB_DIR ${PROJECT_SOURCE_DIR}/install/shared)
set(INSTALL_STATIC_LIB_DIR ${PROJECT_SOURCE_DIR}/install/static)

add_library(add SHARED ${SRC}/add.cpp)
target_include_directories(add PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE add)
set_target_properties(myapp PROPERTIES INSTALL_RPATH ${INSTALL_SHARED_LIB_DIR})

install(TARGETS myapp add
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${INSTALL_SHARED_LIB_DIR})

