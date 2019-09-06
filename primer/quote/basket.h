#ifndef CPP_PRIMER_QUOTE_BASKET_H_
#define CPP_PRIMER_QUOTE_BASKET_H_

#include "quote.h"

#include <memory>
#include <set>
#include <iostream>
#include <utility>


class Basket final
{
public:
  Basket(): items_(Compare)
  {}

  void AddItem(const Quote &val)
  {
    std::cout << "Enter lvalue AddItem" << std::endl;
    items_.insert(Quote::SPtr(val.Clone()));
  }

  void AddItem(Quote &&val)
  {
    std::cout << "Enter rvalue AddItem" << std::endl;
    items_.insert(Quote::SPtr(std::move(val).Clone()));
  }

  double CalculateTotalReceipt(std::ostream &os) const;

private:
  static bool Compare(const Quote::SPtr &lhs, const Quote::SPtr &rhs)
  {
    return lhs->get_isbn() < rhs->get_isbn();
  }
  std::multiset<Quote::SPtr, decltype(Compare)*> items_;
};

#endif  //CPP_PRIMER_QUOTE_BASKET_H_