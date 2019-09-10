#include "repository/IRepository.h"

#include <string>
#include <vector>
#include <map>
#include <memory>

struct FileContent
{
  using SPtr = std::shared_ptr<FileContent>;
  std::string file_name_;
  std::map<std::size_t, std::string> content_;
};

class FileContentRepository: public IRepository<FileContent::SPtr>
{
public:
  using Specification = IRepository<FileContent::SPtr>::Specification;
  using EntityList = IRepository<FileContent::SPtr>::EntityList;

  static FileContentRepository *GetInstance();

  FileContentRepository() = default;

  void AddItem(const FileContent::SPtr &val)
  {
    file_contents_[val.file_name_] = val;
  }

  void AddItem(FileContent::SPtr &&val)
  {
    file_contents_[val.file_name_] = std::move(val);
  }

  void RemoveItems(Specification &spec);

  EntityList Query(Specification &spec);

private:
  static FileContentRepository *instance_;
  std::map<std::string, FileContent::SPtr> file_contents_;
};