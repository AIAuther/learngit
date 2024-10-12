cmake_minimum_required(VERSION 3.2)

project(task1)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(task1 main2.cpp)

target_link_libraries(task1 ${OpenCV_LIBS})

