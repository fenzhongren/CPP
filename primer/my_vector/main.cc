#include "my_vector.h"

#include <iostream>
#include <string>
#include <list>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::list;

int main()
{
  list<string> b{"aa", "bb", "cc"};
  MyVector<string> a = MyVector<string>(b.begin(), b.end());

  for(int i = 0; i<30; i++) {
    a.push_back("kk");
  }
  
  for(auto it = a.begin(); it != a.end(); ++it) {
    cout << *it << " ";
  }
  cout << a.capacity() << " " << a.size() << endl;

  return 0;
}