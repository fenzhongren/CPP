#include "text_query.h"

#include <sstream>
#include <string>
#include <iterator>
#include <utility>
#include <algorithm>
#include <fstream>

void TextQuery::Open(const std::string &file_name)
{
  std::ifstream input(file_name);
  
}

void TextQuery::QueryResult::ShowResult() const
{
  if(!Found()) {
    std::cout << "Did find elememt " << element_ << std::endl;
    return;
  }
  
  std::cout << "Element " << element_ << " occurs " << lines_.size() << " times"
   << std::endl;
  for(const auto &line: lines_) {
    std::cout << "    (line " << line << ") ";
    for(const auto &val: (*lines_sptr_)[line]) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

TextQuery::~TextQuery()
{
  std::cout << "Enter ~TextQuery" << std::endl;
  if(file_name_ != std::string()) {
    Close();
  }
}