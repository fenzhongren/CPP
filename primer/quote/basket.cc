#include "basket.h"

double Basket::CalculateTotalReceipt(std::ostream &os) const
{
  double sum = 0;
  for(auto it = items_.cbegin(); it != items_.cend();
   it = items_.upper_bound(*it)) {
    sum += PrintTotal(os, **it, items_.count(*it));
  }

  return sum;
}