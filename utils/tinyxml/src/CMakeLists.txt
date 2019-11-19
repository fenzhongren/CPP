aux_source_directory(. DIR_SRCS)

add_library(tinyxml ${DIR_SRCS})
target_include_directories(tinyxml PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)