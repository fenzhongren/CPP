#ifndef CPP_DESIGN_PATTERN_OBSERVER_CURRENT_CONDITION_DISPLAY_H_
#define CPP_DESIGN_PATTERN_OBSERVER_CURRENT_CONDITION_DISPLAY_H_

#include "weather_observer.h"

#include <string>

class CurrentConditionDisplay: public WeatherObserver
{
public:
  using WSPtr_t = WeatherSubject *;

  virtual void Update(WeatherEvent we, const WeatherMeasurements &wm);
  virtual bool Register2Subject(WeatherSubject *subject);
  virtual std::string GetClassName() const
  {return "CurrentConditionDisplay";}

  virtual ~CurrentConditionDisplay();

private:
  WSPtr_t subject_ = nullptr; 
};
#endif  //CPP_DESIGN_PATTERN_OBSERVER_CURRENT_CONDITION_DISPLAY_H_