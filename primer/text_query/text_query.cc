#include "text_query.h"

#include <sstream>
#include <string>
#include <iterator>
#include <utility>
#include <algorithm>
#include <fstream>

std::ostream &QueryResult::ShowResult(std::ostream &os) const
{
  if(!IsFound) {
    return os;
  }

  FileContent::SPtr file_content_sptr = file_content_wptr_.lock();
  if(!file_content_sptr) {
    os << "File has closed" << std::endl;
    return os;
  }

  size_t time = line_no_set_csptr_->size();
  os << elememt_ << " occurs " << time << (time > 1 ? "times" : "time")
   << std::endl;
  for(auto it = line_no_set_csptr_->begin(); it != line_no_set_csptr_->end();
   ++it) {
    os << "    (line " << *it <<") " << 
     *(file_content_sptr->GetContentByLineNumber(*it)) << std::endl;
  }

  return os;
}

void TextQuery::Open(const std::string &file_name)
{
  if(IsOpen()) {
    return;
  }

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

QueryResult TextQuery::Query(const std::string &element) const
{
  
}

TextQuery::~TextQuery()
{
  std::cout << "Enter ~TextQuery" << std::endl;
  if(file_name_ != std::string()) {
    Close();
  }
}