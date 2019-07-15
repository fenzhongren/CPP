#ifndef CPP_DESIGN_PATTERN_DECORATOR_BEVERAGE_H_
#define CPP_DESIGN_PATTERN_DECORATOR_BEVERAGE_H_

#include <string>
#include <vector>
#include <memory>

class IBeverage 
{
public:
  using SPtr = std::shared_ptr<IBeverage>;
  virtual std::string GetDescription() const = 0;
  virtual double GetCost() const = 0;

  virtual ~IBeverage() = default;
};

class Beverage: public IBeverage
{
public:
  Beverage() = delete;
  Beverage(double cost, string description): description_(description),
    cost_(cost) {}
  virtual std::string GetDescription() const
    {return "description_";}
  virtual double GetCost() const
    {return cost_;}

  virtual ~IBeverage() = default;

private:
  std::string description_;
  double cost_;
};

#endif  //CPP_DESIGN_PATTERN_DECORATOR_BEVERAGE_H_