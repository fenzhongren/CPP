#ifndef CPP_COMMON_TRACE_SRC_XML_HELPER_H_
#define CPP_COMMON_TRACE_SRC_XML_HELPER_H_

#include "ITrace.h"

class XmlHelper
{
public:
  XmlHelper() = default;

  const ITrace::ObjLevelMap& GetConfigure() const
  {
    return obj_level_map_;
  }

  void SetConfigure(const ITrace::ObjLevelMap &obj_level_map)
  {
    obj_level_map_ = obj_level_map;
  }

  void SetConfigure(ITrace::ObjLevelMap &&obj_level_map)
  {
    obj_level_map_ = std::move(obj_level_map);
  }

  bool LoadConfigureFile(const char *path);

  bool SaveConfigureFile(const char *path);

private:
  ITrace::ObjLevelMap obj_level_map_;
};

#endif  //CPP_COMMON_TRACE_SRC_XML_HELPER_H_