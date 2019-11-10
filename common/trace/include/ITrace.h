#ifndef CPP_COMMON_TRACE_ITRACE_H_
#define CPP_COMMON_TRACE_ITRACE_H_

#include <map>
#include <string>

enum class TraceLevel {
  kError,
  kWarn,
  kInfo,
  kDebug,
  kNone
};

class ITrace
{
public:
  using ObjLevelMap = std::map<std::string, TraceLevel>;
  static ITrace &GetInstance();

  virtual void Init() = 0;
  virtual void Print(const char *obj_str, TraceLevel level,
   const char *fmt, ...) const = 0;

  virtual void AddTraceObj(const char *obj_str, TraceLevel level) = 0;
  virtual void AddTraceObjByXml(const char *file_path) = 0;
};

#endif  //CPP_COMMON_TRACE_ITRACE_H_