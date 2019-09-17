#include "file_content_repository.h"

#include <algorithm>

using std::string

const string *FileContent::GetContentByLineNumber(size_t line_number) const
{

  if(contents_.count(line_number)) {
    return &contents_[line_number];
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
    LineNoSetSPtr lines_sptr = lineSearchElementInFile(element);
    element_in_lines_.AddItem(element, lines_sptr);
    return lines_sptr;
  }
}

LineNoSetSPtr FileContent::SearchElementInFile(const std::string &element)
{
  LineNoSetSPtr lines_sptr = make_shared<std::set<size_t>>();

  for(auto it = contents_.begin(); it != contents_.end(); ++it) {
    istringstream input(it->second);
    istream_iterator<char> in_iter(input);
    istream_iterator<char> eof;
    auto it = std::find(in_iter, eof, element);
    if(it != eof) {
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