#ifndef CPP_DESIGN_PATTERN_DECORATOR_HOUSE_BLEND_H_
#define CPP_DESIGN_PATTERN_DECORATOR_HOUSE_BLEND_H_

#include "beverage.h"

class HouseBlend: public Beverage
{
public:
  HouseBlend(): Beverage(0.89)
  {}

  virtual std::string GetDescription() const
    {return "House Blend";}

  virtual ~HouseBlend() = default;

private:
  double cost_;
};

#endif  //CPP_DESIGN_PATTERN_DECORATOR_HOUSE_BLEND_H_