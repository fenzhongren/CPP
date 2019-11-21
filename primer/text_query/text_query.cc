#include "text_query.h"

#include <sstream>
#include <string>
#include <iterator>
#include <utility>
#include <algorithm>
#include <fstream>

std::ostream &QueryResult::ShowResult(std::ostream &os) const
{
  if(!IsFound()) {
    return os;
  }

  FileContent::CSPtr file_content_csptr = file_content_cwptr_.lock();
  if(!file_content_csptr) {
    os << "Can't find file content, maybe file " << file_name_ <<
     " has closed" << std::endl;
    return os;
  }

  FileContent::LineNoSetCSPtr line_no_set_csptr_ = line_no_set_cwptr_.lock();
  if(!line_no_set_csptr_) {
    os << "Can't fike line nubmers, maybe file has closed" << std::endl;
    return os;
  }

  size_t times = line_no_set_csptr_->size();
  if(0 == times) {
    os << "file " << file_name_ << " doesn't contain element " << elememt_
     << std::endl;

    return os;
  }

  os << elememt_ << " occurs " << times << (times > 1 ? " times" : " time")
   << std::endl;
  for(auto it = line_no_set_csptr_->begin(); it != line_no_set_csptr_->end();
   ++it) {
    os << "    (line " << *it <<") " << 
     *(file_content_csptr->GetContentByLineNumber(*it)) << std::endl;
  }

  return os;
}

void TextQuery::Open(const std::string &file_name)
{
  if(IsOpen(file_name)) {
    file_name_ = file_name;
    return;
  }

  FileContent::SPtr content_sptr = std::make_shared<FileContent>(file_name);

  std::ifstream input(file_name);
  if(!input.is_open()) {
    std::cerr << "Can't open file " << file_name << std::endl;
  }

  file_name_ = file_name;
  size_t line_no = 1;
  for(std::string content; std::getline(input, content);) {
    content_sptr->AddOneLine(line_no, content);
    ++line_no;
  }

  FileContentRepository::GetInstance().AddItem(std::move(content_sptr));
  input.close();
  file_name_ = file_name;
}

QueryResult TextQuery::Query(const std::string &element) const
{
  auto spec_sptr = GetFileNameSpecification(file_name_);
  auto file_content_list =
   FileContentRepository::GetInstance().Query(*spec_sptr);
  if(file_content_list.empty()) {
    return std::move(QueryResult(false));
  }

  FileContent::SPtr content_sptr = file_content_list.front();
  FileContent::LineNoSetCSPtr line_no_set_csptr =
   content_sptr->FindLinesThatContainElement(element);

  QueryResult result = QueryResult(true, file_name_, element);
  result.set_lines(line_no_set_csptr);
  result.set_file_content(content_sptr);

  return std::move(result);
}

TextQuery::~TextQuery()
{
  std::cout << "Enter ~TextQuery" << std::endl;
  if(file_name_ != std::string()) {
    Close();
  }
}