#include "file_content_repository.h"

using std::string

const string *FileContent::GetContentByLineNumber(size_t line_number) const
{

  if(contents_.count(line_number)) {
    return &contents_[line_number];
  } else {
    return nullptr;
  }
}

FileContent::LineNumberSetCSPtr 
 FileContent::FindLinesThatContainElement(const std::string &element)
{
  auto item = element_in_lines_.GetItem(element);
  if(item.first == true) {
    return item.second;
  } else {
    
  }
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