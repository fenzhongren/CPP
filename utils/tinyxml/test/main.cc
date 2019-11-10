#include "tinyxml.h"

#include <iostream>

void build_simple_doc(const char *path)
{
  TiXmlDocument doc;
  TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
  TiXmlElement *element = new TiXmlElement("Hello");
  TiXmlText *text = new TiXmlText("World");
  element->LinkEndChild(text);
  doc.LinkEndChild(decl);
  doc.LinkEndChild(element);
  doc.SaveFile(path);
}

int main()
{
  build_simple_doc("my_test.xml");
  return 0;
}