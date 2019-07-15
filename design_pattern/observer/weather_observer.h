#ifndef CPP_DESIGN_PATTERN_OBSERVER_WEATHER_OBSERVER_H_
#define CPP_DESIGN_PATTERN_OBSERVER_WEATHER_OBSERVER_H_

#include <string>

struct WeatherMeasurements
{
  WeatherMeasurements(): temperature(0), humidity(0), pressure(0)
  {}
  double temperature;
  double humidity;
  double pressure;
};

enum class WeatherEvent
{
  kUpdate,
  kRelease
};

class WeatherSubject;

class WeatherObserver
{
public:
  virtual void Update(WeatherEvent we, const WeatherMeasurements &wm) = 0;
  virtual bool Register2Subject(WeatherSubject *subject) = 0;
  virtual std::string GetClassName() const
  {return "WeatherObserver";}

  virtual ~WeatherObserver() = default;

};

class WeatherSubject
{
public:
  virtual bool RegisterObserver(WeatherObserver *wo) = 0;
  virtual bool RemoveObserver(WeatherObserver *wo) = 0;

  virtual ~WeatherSubject() = default;
};
#endif  //CPP_DESIGN_PATTERN_OBSERVER_WEATHER_OBSERVER_H_