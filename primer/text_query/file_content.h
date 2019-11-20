#ifndef CPP_PRIMER_TEXT_QUERY_FILE_CONTENT_H_
#define CPP_PRIMER_TEXT_QUERY_FILE_CONTENT_H_

#include <map>
#include <set>
#include <string>
#include <memory>

#include "common/cache.h"

class FileContent
{
public:
  using SPtr = std::shared_ptr<FileContent>;
  using CSPtr = std::shared_ptr<const FileContent>;
  using WPtr = std::weak_ptr<FileContent>;
  using CWPtr = std::weak_ptr<const FileContent>;
  using LineNoSetCSPtr = std::shared_ptr<const std::set<size_t>>;

  explicit FileContent(const std::string &file_name): file_name_(file_name),
   element_in_lines_(16)
  {}

  void AddOneLine(size_t line_number, const std::string &content)
  {
    contents_[line_number] = content;
  }

  const std::string& GetContentByLineNumber(size_t line_number) const;

  LineNoSetCSPtr FindLinesThatContainElement(const std::string &element);

  std::string get_file_name() const
  {
    return file_name_;
  }

  virtual ~FileContent();

private:
  using LineNoSetSPtr = std::shared_ptr<std::set<size_t>>;

  LineNoSetCSPtr SearchElementInFile(const std::string &element) const;

  std::string file_name_;
  std::map<size_t, std::string> contents_;

  Cache<std::string, LineNoSetCSPtr> element_in_lines_;
};

#endif  //CPP_PRIMER_TEXT_QUERY_FILE_CONTENT_H_