#ifndef CPP_COMMON_TRACE_TRACE_V1_H_
#define CPP_COMMON_TRACE_TRACE_V1_H_

#include "ITrace.h"

#include <utility>

#include <stdarg.h>

class TraceV1 final: public ITrace
{
public:
  TraceV1();
  TraceV1(const TraceV1 &rhs) = delete;
  TraceV1 &operator=(const TraceV1 &rhs) = delete;

  void SetEnabledObjects(const TraceObject<std::string> &objects) override
  {
    enabled_objects_ = objects;
  }

  void PrintError(const std::string &type, const char *fmt, ...) const override;
  void PrintWarn(const std::string &type, const char *fmt, ...) const override;
  void PrintInfo(const std::string &type, const char *fmt, ...) const override;
  void PrintDebug(const std::string &type, const char *fmt, ...) const override;

private:
  const static size_t kBufSize = 64;

  std::string GetString(const char *fmt, va_list ap)
  {
    char buf[kBufSize];
    vsnprintf(buf, kBufSize, fmt, ap);
    return std::move(std::string(buf))
  }

  TraceObject enabled_objects_;
};

#endif  //CPP_COMMON_TRACE_TRACE_V1_H_