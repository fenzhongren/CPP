#ifndef CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
#define CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <cassert>

#include "my_vector/my_vector.h"
#include "file_content_repository.h"

class TextQuery
{
public:
  
  TextQuery(): file_name_(std::string());
  
  TextQuery(const TextQuery &) = delete;
  
  TextQuery &operator=(const TextQuery &) = delete;
  
  void Open(const std::string &file_name);
  
  bool IsOpen() const
  {
    FileContentSpecificationByFileName spec(file_name_);
    auto list = FileContentRepository.GetInstance().Query(spec);
    return !list.empty();
  }
  
  void Close()
  {
    FileContentSpecificationByFileName spec(file_name_);
    FileContentRepository.GetInstance().RemoveItems(spec);
  }

  QueryResult Query(const std::string &element);

  virtual ~TextQuery();
  
private:
  std::string file_name_;
};

inline void AssertTrue(bool expr, const std::string &msg,
 int line_number, const std::string &file_name)
{
  if(!expr) {
    std::cerr << "Error happens in file " << file_name << " line "
     << line_number << std::endl;
    std:: cerr << msg << std::endl;
    assert(0);
  }
}

inline void AssertFalse(bool expr, const std::string &msg,
 int line_number, const std::string &file_name)
{
  AssertTrue(!expr, msg, line_number, file_name);
}

#define AssertTrue(expr, msg) AssertTrue(expr, msg, __LINE__, __FILE__)

#define AssertFalse(expr, msg) AssertFalse(expr, msg, __LINE__, __FILE__)

#endif  //CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
