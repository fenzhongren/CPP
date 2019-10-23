aux_source_directory(. DIR_SRCS)

add_library(trace ${DIR_SRCS})
target_include_directories(trace PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")