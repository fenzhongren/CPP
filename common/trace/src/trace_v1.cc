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
  return instance;
}

void TraceV1::AddTraceObj(const char *obj_str, TraceLevel level)
{
  std::string obj = obj_str;
  enabled_objects_[obj] = level;
  std::cout << "Add trace obj: " << obj << ", Level: " << Level2Str(level)
   << std::endl;
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

  std::cout << obj_str << " " << Level2Str(level) << ": " << content
   << std::endl;
}

bool TraceV1::IsTraceEnabled(const std::string &obj, TraceLevel level) const
{
  bool result = false;
  if(enabled_objects_.count(obj)) {
    if(level <= enabled_objects_.at(obj)) {
      //std::cout << "Find trace obj: " << obj << ", Level: " <<
       //Level2Str(enabled_objects_.at(obj)) << std::endl;
      result = true;
    }
  }

  return result;
}