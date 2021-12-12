cmake_minimum_required(VERSION 3.12.4)
# 项目名称
project(eventLoop_test)

set(CXX_FLAGS
    -g
    -Wall
    -std=c++11
    -D_PTHREADS
    # -Wno-unused-parameter
)

add_subdirectory (src)