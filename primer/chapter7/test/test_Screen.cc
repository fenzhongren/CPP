#include "Screen.h"

#include <iostream>

using std::cout;
using std::endl;
int main()
{
  Screen my_screen(5, 3, '*');
  const Screen blank(5, 3, '*');
  my_screen.SetValue('#').Display(cout);
  blank.Display(cout);

  return 0;
}