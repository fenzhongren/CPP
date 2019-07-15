#include "Screen.h"

Screen &Screen::Move(PositionType row, PositionType column)
{
  cursor_ = CalculateIndexByPosition(row, column);
  return *this;
}

const Screen &Screen::Display(std::ostream &os) const
{
  DoDisplay(os);
  return *this;
}

Screen &Screen::Display(std::ostream &os)
{
  DoDisplay(os);
  return *this;
}

void Screen::DoDisplay(std::ostream &os) const
{
  os << "start display: " << std::endl;
  for(PositionType row = 0; row != height_; ++row) {
    for(PositionType column = 0; column != width_; ++column) {
      PositionType index = CalculateIndexByPosition(row, column);
      os << context_[index];
    }
    os << std::endl;
  }
}

void ScreenManager::ClearByIndex(ScreenIndex index)
{
  Screen &temp = screen_list_[index];
  temp.context_ = std::vector<char>(temp.height_*temp.width_, ' ');
}
