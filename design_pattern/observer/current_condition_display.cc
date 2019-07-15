#include "current_condition_display.h"

#include <iostream>

using std::cout;
using std::endl;

void CurrentConditionDisplay::Update(WeatherEvent we, 
  const WeatherMeasurements &wm)
{
  cout << "In class " << GetClassName() << endl;
  if(we == WeatherEvent::kUpdate) {
    cout << "Temperature: " << wm.temperature << endl;
    cout << "Humidity: " << wm.humidity << endl;
    cout << "Pressure: " << wm.pressure << endl;
  } else if(we == WeatherEvent::kRelease) {
    cout << "Subject will release!" << endl;
    subject_ = nullptr;
  } else {
    cout << "Unknown Event" << endl;
  }
}

bool CurrentConditionDisplay::Register2Subject(WeatherSubject *subject)
{
  if(subject->RegisterObserver(this)) {
    subject_ = subject;
  }
  return true;
}

CurrentConditionDisplay::~CurrentConditionDisplay()
{
  if(subject_ != nullptr) {
    subject_->RemoveObserver(this);
  }
  subject_ = nullptr;
}