#ifndef CPP_DESIGN_PATTERN_DECORATOR_DARK_ROAST_H_
#define CPP_DESIGN_PATTERN_DECORATOR_DARK_ROAST_H_

#include "beverage.h"

class DarkRoast: public Beverage
{
public:
  DarkRoast(): Beverage(0.99, "Dark Roast")
  {}

  virtual ~DarkRoast() = default;

};

#endif  //CPP_DESIGN_PATTERN_DECORATOR_DARK_ROAST_H_