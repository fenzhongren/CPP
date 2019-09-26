cmake_minimum_required(VERSION 3.9)

project("test query")

include_directories(../)
include_directories(../../)

aux_source_directory(. DIR_SRCS)

add_executable(main ${DIR_SRCS})