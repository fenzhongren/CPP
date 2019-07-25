#ifndef CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_
#define CPP_LOCAL_TEST_TEXT_QUERY_TEXT_QUERY_H_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <cassert>

class TextQuery
{
public:
  using FileLinesMap = std::map<int, std::vector<std::string>>;
  
  TextQuery(): lines_sptr_(nullptr)
  {}
  
  TextQuery(const TextQuery &) = delete;
  
  TextQuery &operator=(const TextQuery &) = delete;
  
  bool Open(const std::string &file_name);
  
  bool IsOpen() const
  {return input_stream.is_open();}
  
  void Close();
  
  class QueryResult
  {
  public:
    QueryResult() = delete;
    explicit QueryResult(const std::string &element): element_(element),
     lines_sptr_(nullptr), found(false)
    {}
    
    bool Found() const
    {return found;}
    
    void ShowResult() const;
    
    virtual ~QueryResult() = default;
    
    friend class TextQuery;
    
  private:
    std::string element_;
    std::shared_ptr<FileLinesMap> lines_sptr_;
    std::set<int> lines_;
    bool found;
  };

  QueryResult Query(const std::string &element);

  virtual ~TextQuery();
  
private:
  bool LoadFile();

  bool HasLoadedFile() const
  {return !(lines_sptr_ == nullptr);}

  std::string file_name_;
  std::ifstream input_stream;
  std::shared_ptr<FileLinesMap> lines_sptr_;
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
