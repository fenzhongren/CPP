#ifndef CPP_COMMON_TRACE_TRACE_H_
#define CPP_COMMON_TRACE_TRACE_H_

#include "ITrace.h"

#define ERROR   TraceLevel::kError
#define WARN    TraceLevel::kWarn
#define INFO    TraceLevel::kInfo
#define DEBUG   TraceLevel::kDebug
#define NONE    TraceLevel::kNone

#define DECLARE_TRACEOBJ(obj)  \
  static TraceObj trace_obj##obj = {.obj_str_ = #obj}

#define TRACE_ERROR(obj, fmt, args...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, ERROR, fmt, args)

#define TRACE_WARN(obj, fmt, args...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, WARN, fmt, args)

#define TRACE_INFO(obj, fmt, args...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, INFO, fmt, args)

#define TRACE_DEBUG(obj, fmt, args...) \
  ITrace::GetInstance().Print(trace_obj##obj.obj_str_, DEBUG, fmt, args)

#endif  //CPP_COMMON_TRACE_TRACE_H_