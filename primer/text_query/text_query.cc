#include "text_query.h"

#include <sstream>
#include <string>
#include <iterator>
#include <utility>
#include <algorithm>

bool TextQuery::Open(const std::string &file_name)
{
  AssertFalse(input_stream.is_open(), "File is already open!");
  
  input_stream.open(file_name);
  if(IsOpen()) {
    file_name_ = file_name;
  }
  
  return IsOpen();
}

void TextQuery::Close()
{
  if(IsOpen()) {
    input_stream.close();
    file_name_ = std::string();
    if(lines_sptr_) {
      lines_sptr_.reset();
    }
  }
}

TextQuery::QueryResult TextQuery::Query(const std::string &element)
{
  if(!HasLoadedFile()) {
    LoadFile();
    AssertTrue(HasLoadedFile(), "Can't load file!");
  }
  
  QueryResult result{element};
  std::set<int> lines;
  for(auto line: *lines_sptr_) {
    if(std::count(line.second.cbegin(), line.second.cend(), element)) {
      lines.insert(line.first);
    }
  }
  if(!lines.empty()) {
    result.found = true;
    result.lines_ = lines;
    result.lines_sptr_ = lines_sptr_;
  }
  
  return result;
}

bool TextQuery::LoadFile()
{
  AssertTrue(IsOpen(), "Haven't open any file!");
  
  std::string temp;
  int line_number = 1;
  auto lines_sptr = std::make_shared<FileLinesMap>();
  while(std::getline(input_stream, temp)) {
    std::istringstream is(temp);
    std::istream_iterator<std::string> it(is), eof;
    std::vector<std::string> content(it, eof);
    lines_sptr->insert(std::make_pair(line_number, content));
    ++line_number;
  }
  
  lines_sptr_ = lines_sptr;
  return true;
}

void TextQuery::QueryResult::ShowResult() const
{
  if(!Found()) {
    std::cout << "Did find elememt " << element_ << std::endl;
    return;
  }
  
  std::cout << "Element " << element_ << " occurs " << lines_.size() << " times"
   << std::endl;
  for(const auto &line: lines_) {
    std::cout << "    (line " << line << ") ";
    for(const auto &val: (*lines_sptr_)[line]) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

TextQuery::~TextQuery()
{
  std::cout << "Enter ~TextQuery" << std::endl;
  if(IsOpen()) {
    std::cout << "Call Close" << std::endl;
    Close();
  }
}