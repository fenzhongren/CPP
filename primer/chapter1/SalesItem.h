#ifndef PRIMER_CHAPTER1_SALES_ITEM_H_
#define PRIMER_CHAPTER1_SALES_ITEM_H_

#include <string>
#include <iostream>

class SalesItem {
public:
  explicit SalesItem(std::string aIsbn=""): isbn_(aIsbn), copies_sold_(0), \
    average_price_(0) {}

  std::string get_isbn() const
  {return isbn_;}

  void set_isbn(const std::string &isbn)
  {isbn_ = isbn;}

  SalesItem& operator+(const SalesItem&) const;
  void operator+=(const SalesItem&);

  friend std::istream& operator>>(std::istream&, SalesItem&);
  friend std::ostream& operator<<(std::ostream&, SalesItem&);

private:
  std::string isbn_;
  int copies_sold_;
  double average_price_;
};

std::istream& operator>>(std::istream&, SalesItem&);

std::ostream& operator<<(std::ostream&, SalesItem&);

#endif  //PRIMER_CHAPTER1_SALES_ITEM_H_