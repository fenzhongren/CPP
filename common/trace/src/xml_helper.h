#ifndef CPP_COMMON_TRACE_SRC_XML_HELPER_H_
#define CPP_COMMON_TRACE_SRC_XML_HELPER_H_

#include "ITrace.h"

class XmlHelper
{
public:
  XmlHelper() = default;
  XmlHelper(const XmlHelper&) = delete;
  XmlHelper &operator=(const XmlHelper&) = delete;

  const ITrace::ObjLevelMap& GetConfigures() const
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

  virtual ~XmlHelper() = default;

private:
  ITrace::ObjLevelMap obj_level_map_;
};

#endif  //CPP_COMMON_TRACE_SRC_XML_HELPER_H_