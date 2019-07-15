#include "weather_data.h"

#include <algorithm>

bool WeatherData::RegisterObserver(WeatherObserver *wo)
{
  auto iter = std::find(observers_.begin(), observers_.end(), wo);
  if(iter == observers_.end()) {
    observers_.push_back(wo);
  }

  return true;
}

bool WeatherData::RemoveObserver(WeatherObserver *wo)
{
  auto iter = std::find(observers_.begin(), observers_.end(), wo);
  if(iter != observers_.end()) {
    observers_.erase(iter);
  }
  return true;
}

void WeatherData::NotifyObservers()
{
  for(auto observer: observers_) {
    observer->Update(WeatherEvent::kUpdate, last_measurement_);
  }
}

void WeatherData::set_status(double temperature, double humidity, 
  double pressure)
{
  last_measurement_.temperature = temperature;
  last_measurement_.humidity = humidity;
  last_measurement_.pressure = pressure;
  NotifyObservers();
}

WeatherData::~WeatherData()
{
  for(auto observer: observers_) {
    observer->Update(WeatherEvent::kRelease, last_measurement_);
  }

  observers_.clear();
}