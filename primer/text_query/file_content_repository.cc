#include "file_content_repository.h"

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