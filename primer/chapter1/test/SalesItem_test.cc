#include "chapter1/SalesItem.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int main()
{
  SalesItem total;

  if(cin >> total) {
    SalesItem trans;
    while(cin >> trans) {
      if(total.get_isbn() == trans.get_isbn()) {
        total += trans;
      } else {
        cout << total << endl;
        total = trans;
      }
    }
    cout << total << endl;
  } else {
    cerr << "No data?!" << endl;
    return -1;
  }

  return 0;
}