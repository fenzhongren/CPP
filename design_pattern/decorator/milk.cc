#include "milk.h"

double Milk::cost() const
{
  return cost_ + get_wrapped_beverage()->cost();
}

std::string Milk::GetDescription() const
{
  return "Milk + " + get_wrapped_beverage()->GetDescription();
}