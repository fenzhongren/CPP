cmake_minimum_required(VERSION 3.9)

project("test trace")

add_definitions(-DUNIT_TEST -DTEST)
add_compile_options(-Wall -O3)

set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(ROOT_DIR "../../../")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../src" ${BIN_DIR}/src)

aux_source_directory(. DIR_SRCS)
add_executable(main ${DIR_SRCS})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(main trace)