add_executable(SalesDataTest main.cc)

target_link_libraries(SalesDataTest SalesData)

add_test(ToDoSalesDataTest SalesDataTest)

add_executable(ScreenTest test_Screen.cc)
target_link_libraries(ScreenTest SalesData)
add_test(ToDoScreenTest ScreenTest)
