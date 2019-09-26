#include "file_content_repository.h"

#include <algorithm>
#include <iterator>
#include <sstream>

using std::string;

const string *FileContent::GetContentByLineNumber(size_t line_number) const
{

  if(contents_.count(line_number)) {
    return &(contents_.at(line_number));
  } else {
    return nullptr;
  }
}

FileContent::LineNoSetCSPtr 
 FileContent::FindLinesThatContainElement(const std::string &element)
{
  auto item = element_in_lines_.GetItem(element);
  if(item.first == true) {
    return item.second;
  } else {
    LineNoSetSPtr lines_sptr = SearchElementInFile(element);
    element_in_lines_.AddItem(element, lines_sptr);
    return lines_sptr;
  }
}

FileContent::LineNoSetSPtr
 FileContent::SearchElementInFile(const std::string &element)
{
  LineNoSetSPtr lines_sptr = std::make_shared<std::set<size_t>>();

  for(auto it = contents_.begin(); it != contents_.end(); ++it) {
    std::istringstream input(it->second);
    std::istream_iterator<std::string> in_iter(input);
    std::istream_iterator<std::string> eof;
    auto iter = std::find(in_iter, eof, element);
    if(iter != eof) {
      lines_sptr->insert(it->first);
    }
  }

  return lines_sptr;
}

void FileContentRepository::RemoveItems(Specification &spec)
{
  for(auto it = file_contents_.cbegin(); it != file_contents_.cend(); ) {
    if(spec(it->second)) {
      it = file_contents_.erase(it);
    } else {
      ++it;
    }
  }
}

FileContentRepository::EntityList
 FileContentRepository::Query(Specification &spec)
{
  EntityList result_list;
  for(auto it = file_contents_.cbegin(); it != file_contents_.cend(); ++it) {
    if(spec(it->second)) {
      result_list.push_back(it->second);
    }
  }

  return std::move(result_list);
}

FileContentRepository::~FileContentRepository()
{
  file_contents_.clear();
}