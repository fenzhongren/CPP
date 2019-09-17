#include "text_query.h"

#include <sstream>
#include <string>
#include <iterator>
#include <utility>
#include <algorithm>
#include <fstream>

void TextQuery::Open(const std::string &file_name)
{
  FileContent::SPtr content_sptr = std::make_shared<FileContent>(file_name);

  std::ifstream input(file_name);
  size_t line_no = 1;
  for(std::string content; std::getline(input, content);) {
    content_sptr->AddOneLine(line_no, content);
    ++line_no;
  }

  FileContentRepository.GetInstance().AddItem(std::move(content_sptr));

  input.close();
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