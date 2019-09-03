#include "my_vector.h"

#include <iostream>
#include <string>
#include <list>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::list;

MyVector<string> Func1(void)
{
  MyVector<string> aa = {"ff", "gg", "hh"};
  return aa;
}

void Show(MyVector<string> &val)
{
  for(decltype(val.size()) i=0; i<val.size(); ++i) {
    cout << val[i] << " ";
  }
  cout << std::endl;
}

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
  const MyVector<string> bb = {"cc", "dd", "ee"};
  for(decltype(bb.size()) i=0; i<bb.size(); ++i) {
    cout << bb[i] << " ";
  }
  cout << endl;

  cout << "Test move constructor" << endl;
  MyVector<string> cc = std::move(Func1());
  Show(cc);
  MyVector<string> dd = std::move(cc);
  Show(dd);

  cout << "Test copy constructor" << endl;
  MyVector<string> ee(a);
  Show(ee);

  cout << "Test operator=&" << endl;
  ee = dd;
  Show(ee);

  cout << "Test operator=&&" << endl;
  ee = std::move(ee);
  Show(ee);
  ee = std::move(a);
  Show(ee);

  return 0;
}