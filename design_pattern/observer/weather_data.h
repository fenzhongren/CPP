#ifndef CPP_DESIGN_PATTERN_OBSERVER_WEATHER_DATA_H_
#define CPP_DESIGN_PATTERN_OBSERVER_WEATHER_DATA_H_

#include "weather_observer.h"

#include <list>

class WeatherData: public WeatherSubject
{
public:
  using WOPtr_t = WeatherObserver *;

  WeatherData() = default;
  WeatherData(const WeatherData&) = delete;
  WeatherData &operator=(const WeatherData&) = delete;

  virtual bool RegisterObserver(WeatherObserver *wo);
  virtual bool RemoveObserver(WeatherObserver *wo);
  virtual void set_status(double temperature, double humidity, double pressure);

  virtual ~WeatherData();

private:
  void NotifyObservers();
  std::list<WOPtr_t> observers_;
  WeatherMeasurements last_measurement_;
};

#endif  //CPP_DESIGN_PATTERN_OBSERVER_WEATHER_DATA_H_