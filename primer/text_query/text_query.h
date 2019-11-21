#ifndef CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
#define CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_

#include <string>
#include <iostream>
#include <memory>

#include "file_content_repository.h"

class QueryResult
{
public:
  explicit QueryResult(bool is_found = false): is_found_(is_found)
  {}

  QueryResult(bool is_found, const std::string &file_name = std::string(),
   const std::string element = std::string()): is_found_(is_found),
    file_name_(file_name), elememt_(element)
  {}

  void set_lines(const FileContent::LineNoSetCSPtr &csptr)
  {
    line_no_set_csptr_ = csptr;
  }

  void set_file_content(const FileContent::CSPtr &csptr)
  {
    file_content_csptr_ = csptr;
  }

  bool IsFound() const
  {
    is_found_;
  }

  std::ostream &ShowResult(std::ostream &os) const;

  virtual ~QueryResult() = default;

private:
  bool is_found_ = false;
  std::string file_name_;
  std::string elememt_;
  FileContent::LineNoSetCSPtr line_no_set_csptr_;
  FileContent::CSPtr file_content_csptr_;
};

class TextQuery
{
public:
  
  TextQuery(): file_name_(std::string())
  {}
  
  TextQuery(const TextQuery &) = delete;
  
  TextQuery &operator=(const TextQuery &) = delete;
  
  void Open(const std::string &file_name);
  
  bool IsOpen(const std::string &file_name) const
  {
    bool result = false;

    auto spec_sptr = GetFileNameSpecification(file_name);
    auto list = FileContentRepository::GetInstance().Query(*spec_sptr);
    if(!list.empty()) {
      result = true;
    }

    return result;
  }
  
  void Close()
  {
    if(file_name_ == std::string()) {
      return;
    }

    auto spec_sptr = GetFileNameSpecification(file_name_);
    FileContentRepository::GetInstance().RemoveItems(*spec_sptr);
    file_name_ = std::string();
  }

  QueryResult Query(const std::string &element) const;

  virtual ~TextQuery();
  
private:
  FileContentSpecificationByFileName::SPtr
    GetFileNameSpecification(const std::string &file_name) const
  {
    FileContentSpecificationByFileName::SPtr spec_sptr =
     std::make_shared<FileContentSpecificationByFileName>(file_name);

    return std::move(spec_sptr);
  }

  std::string file_name_;
};

#endif  //CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
