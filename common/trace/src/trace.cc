#include "trace.h"

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

TraceLevel Str2Level(const std::string &obj)
{
  TraceLevel result = TraceLevel::kNone;
  if(obj == "ERROR") {
    result = TraceLevel::kError;
  } else if(obj == "WARN") {
    result = TraceLevel::kWarn;
  } else if(obj == "INFO") {
    result = TraceLevel::kInfo;
  } else if(obj == "DEBUG") {
    result = TraceLevel::kDebug;
  }

  return result;
}