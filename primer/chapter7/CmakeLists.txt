aux_source_directory(. DIR_SRCS)

add_library(SalesData ${DIR_SRCS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(test)