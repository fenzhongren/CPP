#include "trace_v1.h"

#include <stdio.h>

#include "xml_helper.h"

namespace {
  
  constexpr ssize_t kBufSize = 1024;

};

ITrace& ITrace::GetInstance()
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
  static thread_local char buf[kBufSize];

  if(!IsTraceEnabled(obj_str, level)) {
    return;
  }

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, kBufSize, fmt, ap);
  va_end(ap);

  std::cout << obj_str << " " << Level2Str(level) << ": " << buf
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

void TraceV1::AddTraceObjByXml(const char *file_path)
{
  XmlHelper helper;
  bool load_ok = helper.LoadConfigureFile(file_path);
  if(!load_ok) {
    std::cerr << "Can't load configure file: " << file_path << std::endl;
    return;
  }

  for(auto it=helper.GetConfigures().cbegin();
   it!=helper.GetConfigures().cend(); ++it) {
    AddTraceObj(it->first.c_str(), it->second);
  }
}

std::ostream& TraceV1::Dump(std::ostream &os) const
{
  for(auto it=enabled_objects_.cbegin(); it!=enabled_objects_.cend(); ++it) {
    os << it->first << " = " << Level2Str(it->second) << std::endl;
  }
  return os;
}