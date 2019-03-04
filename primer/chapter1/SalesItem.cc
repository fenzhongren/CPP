#include "SalesItem.h"

#include <iostream>
#include <cstdlib>

using std::istream;
using std::ostream;

SalesItem& SalesItem::operator+(const SalesItem &rval) const
{
  if(this->isbn_ != rval.isbn_) {
    std::abort();
  }

  SalesItem *result = new SalesItem(this->isbn_);
  result->copies_sold_ = this->copies_sold_ + rval.copies_sold_;
  double total_price = this->copies_sold_ * this->average_price_ + \
    rval.copies_sold_ * rval.average_price_;
  result->average_price_ = total_price / result->copies_sold_;

  return *result;
}

void SalesItem::operator+=(const SalesItem &rval)
{
  if(this->isbn_ != rval.isbn_) {
    std::abort();
  }

  double total_price = this->copies_sold_ * this->average_price_ + \
    rval.copies_sold_ * rval.average_price_;

  this->copies_sold_ += rval.copies_sold_;
  this->average_price_ = total_price/this->copies_sold_;
}

istream& operator>>(istream &lval, SalesItem &rval)
{
  lval >> rval.isbn_ >> rval.copies_sold_ >> rval.average_price_;

  return lval;
}

ostream& operator<<(ostream &lval, SalesItem &rval)
{
  lval << rval.isbn_ << " " << rval.copies_sold_ << " " \
    << rval.average_price_;

  return lval;
}