#ifndef CPP_DESIGN_PATTERN_DECORATOR_CONDIMENT_DECORATOR_H_
#define CPP_DESIGN_PATTERN_DECORATOR_CONDIMENT_DECORATOR_H_

#include "beverage.h"

class CondimentDecorator: public IBeverage
{
public:
  CondimentDecorator() = delete;
  CondimentDecorator(double cost, const string description)
    : description_(description), cost_(cost) {} 
  CondimentDecorator(double cost, const string description, SPtr beverage_sptr)
    : description_(description), cost_(cost),
      wrapped_beverage_sptr_(beverage_sptr)
    {}
  CondimentDecorator(const CondimentDecorator&) = delete;
  CondimentDecorator &operator=(const CondimentDecorator&) = delete;

  virtual std::string GetDescription() const
    {return description_;}
  virtual SPtr get_wrapped_beverage()
    {return wrapped_beverage_sptr_;}
  virtual double GetCost() const
    {return cost_;}

  virtual ~CondimentDecorator() = default;

private:
  SPtr wrapped_beverage_sptr_;
  std::string description_;
  double cost_;
};

#endif  //CPP_DESIGN_PATTERN_DECORATOR_CONDIMENT_DECORATOR_H_