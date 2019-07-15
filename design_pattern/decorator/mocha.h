#ifndef CPP_DESIGN_PATTERN_DECORATOR_MOCHA_H_
#define CPP_DESIGN_PATTERN_DECORATOR_MOCHA_H_

#include "condiment_decorator.h"

class Mocha: public CondimentDecorator
{
public:
  Mocha() = default;
  Mocha(IBeverage *beverage): CondimentDecorator(beverage), cost_(0.2)
  {}
  Mocha(const Mocha&) = delete;
  Mocha &operator=(const Mocha&) = delete;

  virtual std::string GetDescription() const
    {return "Mocha + " + get_wrapped_beverage()->GetDescription();}
  virtual double cost() const
    {return cost_ + get_wrapped_beverage()->cost();}

private:
  double cost_;
};

#endif  //CPP_DESIGN_PATTERN_DECORATOR_MOCHA_H_