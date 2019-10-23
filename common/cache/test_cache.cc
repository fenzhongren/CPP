#include "cache.h"

#include <set>
#include <string>
#include <iostream>

using std::set;
using std::string;
using std::cout;
using std::endl;

int main()
{
  Cache<string, set<int>> cache(3);

  set<int> aset = {1, 2, 3};
  cache.AddItem("aa", aset);
  aset.insert(4);
  cache.AddItem("bb", aset);
  aset.insert(6);
  cache.AddItem("cc", aset);

  cache.Debug(cout) << endl;

  auto item = cache.GetItem("aa");
  for(auto val: item.second) {
    cout << val << " ";
  }
  cout << endl;
  cache.Debug(cout) << endl;

  cache.AddItem("dd", aset);
  cache.Debug(cout) << endl;
  item = cache.GetItem("bb");
  cout << item.first << endl;
  cache.Debug(cout) << endl;

  return 0;
}