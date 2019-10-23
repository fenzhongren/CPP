#ifndef CPP_LOCAL_TEST_COMMON_MY_ASSERT_H_
#define CPP_LOCAL_TEST_COMMON_MY_ASSERT_H_

#include <cassert>
#include <iostream>

#define AssertTrue(expr, msg)             \
{                                         \
  if(!(expr)) {                           \
    std::cerr << "Assert error at file " << __FILE__ << " line " << __LINE__; \
    std::cerr << std::endl;               \
    std::cerr << msg << std::endl;        \
    assert(0);                            \
  }                                       \
} 

#define AssertFalse(expr, msg)            \
  AssertTrue(!(expr), (msg))

#endif  //CPP_LOCAL_TEST_COMMON_MY_ASSERT_H_