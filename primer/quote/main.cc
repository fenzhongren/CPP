#include "quote.h"
#include "basket.h"

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

  cout << endl << "Basket test: " << endl;
  Basket basket;
  for(int i=0; i<2; ++i) {
    basket.AddItem(bulk);
    basket.AddItem(BulkQuote("ef", 8.07, 8, 0.80));
  }

  cout << basket.CalculateTotalReceipt(cout) << endl;

  cout << endl << "test rvalue clone:" << endl;
  Quote *quote_p = std::move(basic).Clone();

  return 0;
}