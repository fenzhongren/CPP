cmake_minimum_required(VERSION 3.10)

project("Decorator Pattern")

aux_source_directory(. DIR_SRCS)

add_executable(main ${DIR_SRCS})