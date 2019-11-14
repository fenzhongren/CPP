#ifndef CPP_COMMON_TRACE_TRACE_H_
#define CPP_COMMON_TRACE_TRACE_H_

#include "ITrace.h"

#include <iostream>

struct TraceObj
{
  const char *obj_str_;
};

inline void InitTrace()
{
  ITrace::GetInstance().Init();
}

inline void AddConfigures2Trace(const char* path)
{
  ITrace::GetInstance().AddTraceObjByXml(path);
}

inline void DumpTrace()
{
  ITrace::GetInstance().Dump(std::cout);
}

#define ERROR   TraceLevel::kError
#define WARN    TraceLevel::kWarn
#define INFO    TraceLevel::kInfo
#define DEBUG   TraceLevel::kDebug
#define NONE    TraceLevel::kNone

#define DECLARE_TRACEOBJ(obj)  \
  static TraceObj trace_obj##obj __attribute__((unused)) = {.obj_str_ = #obj} 

#define TRACE_ERROR(obj, fmt, args...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, ERROR, fmt, args)

#define TRACE_WARN(obj, fmt, args...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, WARN, fmt, args)

#define TRACE_INFO(obj, fmt, ...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, INFO, fmt, __VA_ARGS__)

#define TRACE_DEBUG(obj, fmt, ...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, DEBUG, fmt, __VA_ARGS__)

#endif  //CPP_COMMON_TRACE_TRACE_H_