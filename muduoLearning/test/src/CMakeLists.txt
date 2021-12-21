aux_source_directory (. SRC_LIST)

include_directories (../include)


# 测试用的文件夹
include_directories (../accordingBook)
aux_source_directory (../accordingBook BOOK_DIRECTION)

# 设置包含main的文件
set(INCLUDE_MAIN ../testCode/testP289.cc)

add_executable (test ${SRC_LIST} ${INCLUDE_MAIN} ${BOOK_DIRECTION})
target_link_libraries(test pthread)


# 设置输出路径
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/binTest)
