#include "trace.h"

int main()
{
  init_trace();

  TRACE_ERROR("test1", "aaa %d", 10);
  TRACE_WARN("test2", "bbb %d", 10);
  TRACE_INFO("test2", "ccc %d", 10);
  TRACE_DEBUG("test1", "ddd %d", 10);
  TRACE_DEBUG("test3", "ddd %d", 10);
}