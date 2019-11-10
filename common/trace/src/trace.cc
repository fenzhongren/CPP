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