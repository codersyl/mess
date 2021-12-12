cmake_minimum_required(VERSION 3.12.4)
# 项目名称
project(eventLoop_test)

add_compile_options(-std=c++11 -Wall -g -lpthread) 

add_subdirectory (src)
