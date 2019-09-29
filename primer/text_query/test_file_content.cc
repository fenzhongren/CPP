#include "file_content.h"

#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
  string file_name;

  cout << "Enter a file name: ";
  while(cin >> file_name) {
    ifstream input(file_name);
    if(input.is_open()) {
      
    }
  }
}