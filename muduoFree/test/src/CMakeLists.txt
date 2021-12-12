aux_source_directory (. SRC_LIST)

include_directories (../include)

# 设置包含main的文件
set(INCLUDE_MAIN ../testCode/test_negative_EventLoop.cc)

add_executable (test ${SRC_LIST} ${INCLUDE_MAIN})
target_link_libraries(test pthread)

# 设置输出路径
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/binTest)
