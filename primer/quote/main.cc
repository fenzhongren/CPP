#include "quote.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
  Quote basic("aa", 7.21);
  BulkQuote bulk("bb", 6.94, 5, 0.85);
  LimitedQuote limited("cc", 9.31, 10, 0.8);

  basic.Debug(cout);
  bulk.Debug(cout);
  limited.Debug(cout);

  PrintTotal(cout, basic, 21);
  PrintTotal(cout, bulk, 7);
  PrintTotal(cout, limited, 5);

  cout << endl << "Copy control test:" << endl;
  bulk = BulkQuote("dd", 4.65, 8, 0.9);
  bulk.Debug(cout);

  return 0;
}