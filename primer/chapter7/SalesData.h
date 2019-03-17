#ifndef CPP_PRIMER_CHAPTER7_SALES_DATA_H_
#define CPP_PRIMER_CHAPTER7_SALES_DATA_H_

#include <iostream>
#include <string>

class SalesData
{
public:
  SalesData(const std::string &isbn = " ", unsigned units_sold = 0, double revenue = 0): \
    isbn_(isbn), units_sold_(units_sold), revenue_(revenue) {}

  std::string get_isbn() const
  {
    return isbn_;
  }
  void set_isbn(const std::string &isbn)
  {
    isbn_ = isbn;
  }

  unsigned get_units_sold() const
  {
    return units_sold_;
  }

  void set_units_sold(unsigned units_sold)
  {
    units_sold_ = units_sold;
  }

  double get_revene() const
  {
    return revenue_;
  }

  void set_revenue(double revene)
  {
    revenue_ = revene;
  }

  void setSalesData(const std::string &isbn, unsigned units_sold, double revenue);

  SalesData &combine(const SalesData &rhs);

  friend std::ostream &Print(std::ostream &stream, const SalesData &data);

private:
  std::string isbn_;
  unsigned units_sold_;
  double revenue_;
};

SalesData Add(const SalesData &lhs, const SalesData &rhs);
std::istream &Read(std::istream &stream, SalesData &data);
#endif	//CPP_PRIMER_CHAPTER7_SALES_DATA_H_