cmake_minimum_required(VERSION 3.10)

project(rbt)
set(SOURCE rb_tree.hpp)
set(TESTSOURCE test.cpp)
set(COMPILEROPTIONS -std=c++11 -Wall -pedantic -g)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE} ${TESTSOURCE})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${COMPILEROPTIONS})
