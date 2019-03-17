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
        total.combine(trans);
      } else {
        Print(cout, total);
        total = trans;
      }
    }
    Print(cout, total) << endl;
  } else {
    cerr << "No data?!" << endl;
  }
}