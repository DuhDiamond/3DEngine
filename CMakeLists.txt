cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
project(3DEngine VERSION 0.1)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(3DEngine src/main.cpp src/shader.cpp)
target_include_directories(3DEngine PRIVATE include)
target_link_libraries(3DEngine PRIVATE glad glfw OpenGL::GL)