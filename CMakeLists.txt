cmake_minimum_required(VERSION 3.12)
project(stat906)

set(CMAKE_CXX_STANDARD 14)
include_directories(./include)

find_package(PythonLibs 2.7)
add_executable(stat906 main.cpp include/LCRND.h include/matplotlibcpp.h include/q2.h q2.cpp)

target_include_directories(stat906 PRIVATE /usr/include/python2.7)
target_link_libraries(stat906 python2.7)

#target_link_libraries(stat906 ${PYTHON_LIBRARIES})