#ifndef CPP_PRIMER_CHAPTER7_SCREEN_H_
#define CPP_PRIMER_CHAPTER7_SCREEN_H_

#include <iostream>
#include <vector>

class ScreenManager;

class Screen
{
public:
  using PositionType = std::string::size_type;
  Screen() = default;
  Screen(PositionType height, PositionType width, char ch): height_(height),
    width_(width), cursor_(0), context_(height*width, ch) {}

  char GetValue() const
  {
    return context_[cursor_];
  }

  char GetValueByPosition(PositionType row, PositionType column) const
  {
    PositionType index = CalculateIndexByPosition(row, column);
    return context_[index];
  }

  Screen &SetValue(char ch)
  {
    context_[cursor_] = ch;
    return *this;
  }

  Screen &SetValueByPosition(PositionType row, PositionType column, char ch)
  {
    PositionType index = CalculateIndexByPosition(row, column);
    context_[index] = ch;
    return *this;
  }

  Screen &Move(PositionType row, PositionType column);

  const Screen &Display(std::ostream &os) const;

  Screen &Display(std::ostream &os);

  friend ScreenManager;

//  using PositionType = std::string::size_type;
private:
  void DoDisplay(std::ostream &os) const;
  PositionType CalculateIndexByPosition(PositionType row, 
    PositionType column) const
  {
    return row * width_ + column;
  }

  PositionType height_ = 0;
  PositionType width_ = 0;
  PositionType cursor_ = 0;
  std::vector<char> context_;
};

class ScreenManager
{
public:
  using ScreenIndex = std::vector<Screen>::size_type;
  void ClearByIndex(ScreenIndex index);
private:
  std::vector<Screen> screen_list_ = {Screen(24, 40, ' ')};
};

#endif  //CPP_PRIMER_CHAPTER7_SCREEN_H_