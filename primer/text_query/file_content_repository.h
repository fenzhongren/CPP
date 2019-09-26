#include "repository/IRepository.h"

#include <string>
#include <map>
#include <set>
#include <memory>

#include "specification/composite_specification.h"
#include "common/cache.h"

class FileContent
{
public:
  using SPtr = std::shared_ptr<FileContent>;
  using CSPtr = std::shared_ptr<const FileContent>;
  using WPtr = std::weak_ptr<FileContent>;
  using CWPtr = std::weak_ptr<const FileContent>;
  using LineNoSetSPtr = std::shared_ptr<std::set<size_t>>;
  using LineNoSetCSPtr = std::shared_ptr<const std::set<size_t>>;
  using LineNoSetCWPtr = std::weak_ptr<const std::set<size_t>>;

  explicit FileContent(std::string &file_name): file_name_(file_name),
   element_in_lines_(16)
  {}

  void AddOneLine(size_t line_number, const std::string &content)
  {
    contents_[line_number] = content;
  }

  const std::string *GetContentByLineNumber(size_t line_number) const;

  LineNoSetCSPtr FindLinesThatContainElement(const std::string &element);

  std::string get_file_name() const
  {
    return file_name_;
  }

private:
  LineNoSetSPtr SearchElementInFile(const std::string &element);

  std::string file_name_;
  std::map<size_t, std::string> contents_;

  Cache<std::string, LineNoSetSPtr> element_in_lines_;
};

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

  void RemoveItems(Specification &spec) override;

  EntityList Query(Specification &spec) override;

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

  bool IsSatisfiedBy(const FileContent::SPtr &s_ptr)
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