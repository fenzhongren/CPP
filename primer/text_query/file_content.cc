#include "file_content.h"

#include <sstream>
#include <iterator>
#include <iostream>

using std::string;

const string& FileContent::GetContentByLineNumber(size_t line_number) const
{
  return contents_.at(line_number);
}

FileContent::LineNoSetCSPtr 
 FileContent::FindLinesThatContainElement(const std::string &element)
{
  auto item = element_in_lines_.GetItem(element);
  if(item.first == true) {
    return item.second;
  } else {
    LineNoSetCSPtr lines_csptr = SearchElementInFile(element);
    element_in_lines_.AddItem(element, lines_csptr);
    return lines_sptr;
  }
}

FileContent::LineNoSetCSPtr
 FileContent::SearchElementInFile(const std::string &element) const
{
  LineNoSetSPtr lines_sptr = std::make_shared<std::set<size_t>>();

  for(auto it = contents_.begin(); it != contents_.end(); ++it) {
    std::istringstream input(it->second);
    std::istream_iterator<string> in_iter(input);
    std::istream_iterator<string> eof;
    auto iter = std::find(in_iter, eof, element);
    if(iter != eof) {
      lines_sptr->insert(it->first);
    }
  }

  return lines_sptr;
}

FileContent::~FileContent()
{
  std::cout << "destructor file " << file_name_ << std::endl;
}