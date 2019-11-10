#include "xml_help.h"

#include <iostream>

#include "tinyxml.h"

bool XmlHelper::LoadConfigureFile(const char *path)
{
  TiXmlDocument doc(path);
  if(!doc.LoadFile()) {
    std::cerr << "Can't open config file: " << *path << std::endl;
    return false;
  }

  TiXmlHandle h_doc(&doc);
  TiXmlElement* p_elem;


  p_elem = h_doc.FirstChildElement("configs").Element();
  if(!p_elem) {
    std::cerr << "Config file: " << *path << " is invalid" << std::endl;
    return false;
  }

  TiXmlHandle h_configs(p_elem);
  TiXmlElement* p_trace_obj =
   h_configs.FirstChild("TraceObjs").FirstChild().Element();
  if(!p_trace_obj) {
    std::cerr << "Can't find any trace objs in file: " << *path << std::endl;
    return false;
  }

  obj_level_map_.clear();
  for(p_trace_obj; p_trace_obj; p_trace_obj=p_trace_obj->NextSiblingElement()) {
    TiXmlHandle h_trace_obj(p_trace_obj);
    TiXmlElement* p_name = h_trace_obj.FirstChild("name");
    TiXmlElement* p_level = h_trace_obj.FirstChild("level");
    if(!p_name || !p_level) {
      continue;
    }

  }
}