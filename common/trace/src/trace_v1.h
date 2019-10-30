#ifndef CPP_COMMON_TRACE_TRACE_V1_H_
#define CPP_COMMON_TRACE_TRACE_V1_H_

#include "ITrace.h"

#include <utility>
#include <map>
#include <string>

#include <stdarg.h>

class TraceV1 final: public ITrace
{
public:
  TraceV1() = default;
  TraceV1(const TraceV1 &rhs) = delete;
  TraceV1 &operator=(const TraceV1 &rhs) = delete;

  void Init() override
  {
#ifdef LOCAL_TEST
    AddTraceObj("Test1", TraceLevel::kError);
    AddTraceObj("Test2", TraceLevel::kInfo);
#endif
  }

  void AddTraceObj(const char *obj_str, TraceLevel level) override;

  void Print(const char *obj_str, TraceLevel level,
   const char *fmt, ...) const override;

private:

  bool IsTraceEnabled(const std::string &obj, TraceLevel level) const;

  std::map<std::string, TraceLevel> enabled_objects_;
};
#endif  //CPP_COMMON_TRACE_TRACE_V1_H_