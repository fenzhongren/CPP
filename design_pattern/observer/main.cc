#include "current_condition_display.h"
#include "weather_data.h"

#include <iostream>

using std::cout;
using std::endl;
int main()
{
  CurrentConditionDisplay *observer = new CurrentConditionDisplay();
  WeatherData *subject = new WeatherData();

  cout << observer->GetClassName() << endl;
  observer->Register2Subject(subject);
  subject->set_status(2.0, 3.0, 4.9);

  delete observer;
  delete subject;
  return 0;
}