#include "trace_v1.h"

#include <iostream>
#include <stdio.h>

ITrace &ITrace::GetInstance()
{
  static TraceV1 instance;
  return instance
}

#define DO_TRACE()  \
  if(!enabled_objects_.IsEnabled(type)) \
    return;                             \
                                        \
  va_list ap;                           \
  va_start(ap, fmt);                    \
  string str = GetString(fmt, ap);      \
  va_end(ap);

void TraceV1::PrintError(const std::string &type, const char *fmt, ...) const
{
  DO_TRACE()

  std::cout <<"Error: " << str << std::endl;
}

void PrintWarn(const std::string &type, const char *fmt, ...) const
{
  DO_TRACE();

  std::cout <<"Warning: " << str << std::endl;
}

void PrintInfo(const std::string &type, const char *fmt, ...) const
{
  DO_TRACE();

  std::cout <<"Info: " << str << std::endl;
}

void PrintDebug(const std::string &type, const char *fmt, ...) const
{
  DO_TRACE();

  std::cout <<"Debug: " << str << std::endl;
}