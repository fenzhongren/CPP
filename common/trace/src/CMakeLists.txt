set(USE_TRACE_V1 ON CACHE BOOL "Enable trace version 1")
set(USE_TRACE_V2 OFF CACHE BOOL "Enable trace version 2")

add_subdirectory(${ROOT_DIR}/utils/tinyxml ${BIN_DIR}/tinyxml)

if (USE_TRACE_V1)
  set(DIR_SRCS trace_v1.cc)
elseif (USE_TRACE_V2)
  message("Currently we don't support trace version 2!")
else ()
  message("Use trace version 1 as default.")
  set(DIR_SRCS trace_v1.cc)
endif ()

set(DIR_SRCS ${DIR_SRCS} xml_helper.cc trace.cc)

add_library(trace ${DIR_SRCS})
target_include_directories(trace PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(trace PUBLIC "${ROOT_DIR}/utils/tinyxml/include")
target_link_libraries(trace tinyxml)