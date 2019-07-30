aux_source_directory(. DIR_SRCS)

add_executable(main ${DIR_SRCS})

add_test(main_test main ${TEST_DATA_DIR}/book.txt)
