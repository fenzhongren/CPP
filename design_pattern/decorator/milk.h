#ifndef CPP_DEFIGN_PATTERN_DECORATOR_MILK_H_
#define CPP_DEFIGN_PATTERN_DECORATOR_MILK_H_

#include "condiment_decorator.h"

class Milk: public CondimentDecorator
{
public:
  Milk() = delete;
  Milk(SPtr beverage_sptr): CondimentDecorator(beverage_sptr), cost_(0.1)
  {}
  Milk(const Milk&) = delete;
  Milk &operator=(const Milk&) = delete;

  virtual std::string GetDescription() const;
  virtual double cost() const;

private:
  double cost_;
};

#endif  //CPP_DEFIGN_PATTERN_DECORATOR_MILK_H_