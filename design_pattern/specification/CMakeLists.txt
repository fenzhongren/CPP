cmake_minimum_required(VERSION 3.10)

project("Specification Pattern")


enable_testing()

include_directories(export)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(test)
