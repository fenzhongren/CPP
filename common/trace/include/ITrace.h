#ifndef CPP_COMMON_TRACE_ITRACE_H_
#define CPP_COMMON_TRACE_ITRACE_H_

class enum TraceLevel {
  kError;
  kWarn;
  kInfo;
  kDebug;
  kNone
};

struct TraceObj
{
  const char *obj_str_;
};


class ITrace
{
public:
  static ITrace &GetInstance();

  virtual void Init() = 0;
  virtual void Print(const char *obj_str, TraceLevel level,
   const char *fmt, ...) const = 0;

  virtual void AddTraceObj(const char *obj_str, TraceLevel level) = 0;
};

#endif  //CPP_COMMON_TRACE_ITRACE_H_