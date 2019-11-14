#include "trace.h"

DECLARE_TRACEOBJ(Test1);
DECLARE_TRACEOBJ(Test2);
DECLARE_TRACEOBJ(Test3);
DECLARE_TRACEOBJ(Test4);

int main()
{
  InitTrace();
  AddConfigures2Trace("./trace_objs.xml");
  DumpTrace();
#if 0
  TRACE_ERROR(Test1, "aaa %d", 10);
  TRACE_WARN(Test1, "bbb %d", 10);
  TRACE_INFO(Test2, "ccc %d", 10);
  TRACE_ERROR(Test2, "ddd %d", 10);
  TRACE_DEBUG(Test2, "ddd %d", 10);
#endif
}