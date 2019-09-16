#include "repository/IRepository.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include "specification/composite_specification.h"
#include "common/cache.h"

class FileContent
{
public:
  using SPtr = std::shared_ptr<FileContent>;
  using LineNumberSetSPtr = std::shared_ptr<std::set<size_t>>;
  using LineNumberSetCSPtr = std::shared_ptr<const std::set<size_t>>;
  explicit FileContent(std::file_name): file_name_(file_name),
   element_in_lines_{16}
  {}

  void AddOneLine(size_t line_number, const std::string &content)
  {
    contents_[line_number] = content;
  }

  const std::string *GetContentByLineNumber(size_t line_number) const;

  LineNumberSetCSPtr FindLinesThatContainElement(const std::string &element);

  std::string get_file_name() const
  {
    return file_name_;
  }

private:
  LineNumberSetSPtr SearchElementInFile(const std::string &element);
  std::string file_name_;
  std::map<size_t, std::string> contents_;

  Cache<std::string, LineNumberSetSPtr> element_in_lines_
};

class FileContentRepository: public IRepository<FileContent::SPtr>
{
public:
  using Specification = IRepository<FileContent::SPtr>::Specification;
  using EntityList = IRepository<FileContent::SPtr>::EntityList;

  static FileContentRepository &GetInstance()
  {semaphores
    static FileContentRepository instance;
    return instance;
  }

  FileContentRepository(const FileContentRepository &) = delete;
  FileContentRepository &operator=(const FileContentRepository &) = delete;

  void AddItem(const FileContent::SPtr &val)
  {
    file_contents_[val->get_file_name()] = val;
  }

  void AddItem(FileContent::SPtr &&val)
  {
    file_contents_[val->get_file_name()] = std::move(val);
  }

  void RemoveItems(Specification &spec);

  EntityList Query(Specification &spec);

  virtual ~FileContentRepository();

private:
  FileContentRepository() = default;
  std::map<std::string, FileContent::SPtr> file_contents_;
};

class FileContentSpecificationByFileName:
 public CompositeSpecification<FileContent::SPtr>
{
public:
  FileContentSpecificationByFileName() = delete;
  explicit FileContentSpecificationByFileName(const std::string &file_name):
   CompositeSpecification<FileContent::SPtr>(), file_name_(file_name)
  {}

  bool IsSatisfiedBy(const FileContent::SPtr &s_ptr)
  {
    bool result = false;
    if(s_ptr->get_file_name() == file_name_) {
      result = true;
    }
    return result;
  }


private:
  std::stting file_name_;
};