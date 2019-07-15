#include "SalesData.h"

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;

int main()
{ 
  SalesData total;
  if(Read(cin, total)) {
    SalesData trans;
    while(Read(cin, trans)) {
      if(total.get_isbn() == trans.get_isbn()) {
        total.Combine(trans);
      } else {
        Print(cout, total) << endl;
        total = trans;
      }
    }
    Print(cout, total) << endl;
  } else {
    cerr << "No data?!" << endl;
    return -1;
  }

  return 0;
}