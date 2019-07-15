#include "house_blend.h"
#include "dark_roast.h"
#include "milk.h"
#include "mocha.h"

#include <iostream>

using std::cout;
using std::endl;

void Show(const IBeverage *be)
{
  cout << be->GetDescription() << endl;
  cout << be->cost() << endl;
}

int main()
{
  IBeverage *hb_ptr = new HouseBlend();
  IBeverage *mk_ptr = new Milk(hb_ptr);
  IBeverage *mh_ptr = new Mocha(mk_ptr);

  Show(mh_ptr);
  return 0;
}