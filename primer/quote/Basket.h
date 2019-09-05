#ifndef CPP_PRIMER_QUOTE_BASKET_H_
#define CPP_PRIMER_QUOTE_BASKET_H_

#include "quote.h"

#include <memory>
#include <set>


class Basket final
{
public:
  void AddItem(const Quote &val);
  void AddItem(Quote &&val);

private:
  static bool Compare(const Quote::SPtr &lhs, const Quote::SPtr &rhs)
  {
    return lhs.get_isbn() < rhs.get_isbn();
  }
  std::mutiset<Quote::SPtr, decltype(Compare)*> items_;
}

#endif  //CPP_PRIMER_QUOTE_BASKET_H_