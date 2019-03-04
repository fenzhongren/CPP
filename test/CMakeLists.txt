cmake_minimum_required(VERSION 3.10)

project(Demo1)

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

option (USE_MYMATH "Use provided math implementation" ON)

if(USE_MYMATH)
  include_directories("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory(math)
  set(EXTRA_LIBS ${EXTRA_LIBS} math_functions)
else()
  set(EXTRA_LIBS ${EXTRA_LIBS} m)
endif(USE_MYMATH)

aux_source_directory(. DIR_SRCS)

add_executable(demo ${DIR_SRCS})

target_link_libraries(demo ${EXTRA_LIBS})

add_test(demo_test demo)
