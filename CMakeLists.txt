cmake_minimum_required(VERSION 2.8.7)

include_directories(include)
file(GLOB LIB_SOURCES "src/*.cpp")

project(lab8)
# to build executable target with name a.out
add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase-cpp progbase ssl jansson)
SET(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Wall")
