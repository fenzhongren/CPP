#include "file_content.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::make_shared;

string prompt(const string &st)
{
  string temp;
  cout << st;
  cin >> temp;
  return temp;
}

int main()
{
  string file_name;

  cout << "Enter a file name(quit to quit): ";
  while(cin >> file_name) {

    if(file_name == "quit") {
      cout << "Goodbye" << endl;
      break;
    }

    ifstream input(file_name);
    if(!input.is_open()) {
      cerr << "Can't open file " << file_name << endl;
      cout << "Enter a file name: ";
      continue;
    }
    auto file_content_sptr = make_shared<FileContent>(file_name);
    string temp;
    size_t line_no = 1;
    while(std::getline(input, temp)) {
      file_content_sptr->AddOneLine(line_no, temp);
      ++line_no;
    }

    string element;
    cout << "Enter your string to search(quit to quit): ";
    while(cin >> element) {
      if(element == "quit") {
        break;
      }
      auto line_no_set_csptr =
       file_content_sptr->FindLinesThatContainElement(element);

      auto times = line_no_set_csptr->size();
      cout << "string " << element << " occurs " << times <<
       (times > 1 ? " times" : " time") << endl;

      if(times == 0) {
        cout << "Enter your string to search(quit to quit): ";
        continue;
      }

      for(auto line_no: *line_no_set_csptr) {
        cout << "  (line " << line_no  << ")" <<
         *(file_content_sptr->GetContentByLineNumber(line_no)) << endl;
      }

      cout << "Enter your string to search(quit to quit): ";
    }

    cout << "Enter a file name(quit to quit): ";
  }
}