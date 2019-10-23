#include "trace_v1.h"

#include <iostream>
#include <stdio.h>

namespace {
  std::string Level2Str(TraceLevel level)
  {
    std::string result;

    switch(level) {
    case TraceLevel::kError:
      result = "ERROR";
      break;
    case TraceLevel::kWarn:
      result = "WARN";
      break;
    case TraceLevel::kInfo:
      result = "INFO";
      break;
    case TraceLevel::kDebug:
      result = "DEBUG";
      break;
    default:
      result = "NONE";
      break;
    }

    return std::move(result);
  }
};

ITrace &ITrace::GetInstance()
{
  static TraceV1 instance;
  return instance
}

void TraceV1::Init()
{
  AddTraceObj("Test1", ERROR);
  AddTraceObj("Test2", INFO);
}

void TraceV1::Print(const char *obj_str, TraceLevel level,
   const char *fmt, ...) const
{
  if(!IsTraceEnabled(obj_str, level)) {
    return;
  }

  va_list ap;
  va_start(ap, fmt);
  std::string content = GetString(fmt, ap);
  va_end(ap);

  std::cout << Level2Str(level) << ": " << content << std::endl;
}

bool TraceV1::IsTraceEnabled(const std::string &obj_str, TraceLevel level) const
{
  bool result = false;
  if(enabled_objects_.count(obj_str)) {
    if(enabled_objects_[obj_str] <= level) {
      result = true;
    }
  }

  return result;
}