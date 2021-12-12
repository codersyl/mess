aux_source_directory (. SRC_LIST)

include_directories (../include)

add_executable (main ${SRC_LIST})

# 设置输出路径
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/binTest)