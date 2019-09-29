#include "repository/IRepository.h"

#include <string>
#include <memory>

#include "specification/composite_specification.h"

class FileContentRepository: public IRepository<FileContent::SPtr>
{
public:
  using Specification = typename IRepository<FileContent::SPtr>::Specification;
  using EntityList = typename IRepository<FileContent::SPtr>::EntityList;

  static FileContentRepository &GetInstance()
  {
    static FileContentRepository instance;
    return instance;
  }

  FileContentRepository(const FileContentRepository &) = delete;
  FileContentRepository &operator=(const FileContentRepository &) = delete;

  void AddItem(const FileContent::SPtr &val) override
  {
    file_contents_[val->get_file_name()] = val;
  }

  void AddItem(FileContent::SPtr &&val) override
  {
    file_contents_[val->get_file_name()] = std::move(val);
  }

  void RemoveItems(const Specification &spec) override;

  EntityList Query(const Specification &spec) override;

  virtual ~FileContentRepository();

private:
  FileContentRepository() = default;
  std::map<std::string, FileContent::SPtr> file_contents_;
};

class FileContentSpecificationByFileName:
 public CompositeSpecification<FileContent::SPtr>
{
public:
  using SPtr = typename CompositeSpecification<FileContent::SPtr>::SPtr;
  
  FileContentSpecificationByFileName() = delete;
  explicit FileContentSpecificationByFileName(const std::string &file_name):
   CompositeSpecification<FileContent::SPtr>(), file_name_(file_name)
  {}

  virtual bool IsSatisfiedBy(const FileContent::SPtr &s_ptr) const override
  {
    bool result = false;
    if(s_ptr->get_file_name() == file_name_) {
      result = true;
    }
    return result;
  }

  virtual ~FileContentSpecificationByFileName() = default;

private:
  std::string file_name_;
};