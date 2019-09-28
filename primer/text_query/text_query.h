#ifndef CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
#define CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>

#include "file_content_repository.h"

class QueryResult
{
  QueryResult() = delete;
  QueryResult(bool is_found, const std::string &file_name = "",
   const std::string element = ""): is_found_(is_found), file_name_(file_name),
    elememt_(element)
  {}

  void set_lines(FileContent::LineNoSetCSPtr &csptr)
  {
    line_no_set_cwptr_ = csptr;
  }

  void set_file_content(FileContent::CSPtr &csptr)
  {
    file_content_cwptr_ = csptr;
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
  FileContent::LineNoSetCWPtr line_no_set_cwptr_;
  FileContent::CWPtr file_content_cwptr_;
};

class TextQuery
{
public:
  
  TextQuery() = default;
  
  TextQuery(const TextQuery &) = delete;
  
  TextQuery &operator=(const TextQuery &) = delete;
  
  void Open(const std::string &file_name);
  
  bool IsOpen() const
  {
    auto spec_sptr = GetFileNameSpecification();
    auto list = FileContentRepository::GetInstance().Query(*spec_sptr);
    return !list.empty();
  }
  
  void Close()
  {
    auto spec_sptr = GetFileNameSpecification();
    FileContentRepository::GetInstance().RemoveItems(*spec_sptr);
  }

  QueryResult Query(const std::string &element) const;

  virtual ~TextQuery();
  
private:
  FileContentSpecificationByFileName::SPtr GetFileNameSpecification() const
  {
    FileContentSpecificationByFileName::SPtr spec_sptr =
     std::make_shared<FileContentSpecificationByFileName>(file_name_);

    return std::move(spec_sptr);
  }

  std::string file_name_;
};

#endif  //CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
