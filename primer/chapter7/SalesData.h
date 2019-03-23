#ifndef CPP_PRIMER_CHAPTER7_SALES_DATA_H_
#define CPP_PRIMER_CHAPTER7_SALES_DATA_H_

#include <iostream>
#include <string>

class SalesData
{
public:
  SalesData() : units_sold_(0), revenue_(0) {}
  SalesData(const std::string &isbn) : isbn_(isbn), units_sold_(0),
    revenue_(0) { }
  SalesData(const std::string &isbn, unsigned units_sold, double price) :
    isbn_(isbn), units_sold_(units_sold), revenue_(units_sold * price)
  { }

  SalesData(std::istream &is);

  std::string get_isbn() const
  {
    return isbn_;
  }
  void set_isbn(const std::string &isbn)
  {
    isbn_ = isbn;
  }

  void SetSalesData(const std::string &isbn, unsigned units_sold, double revenue);

  SalesData &Combine(const SalesData &rhs);

  friend std::ostream &Print(std::ostream &os, const SalesData &data);
  friend SalesData Add(const SalesData &lhs, const SalesData &rhs);
  friend std::istream &Read(std::istream &is, SalesData &data);

private:
  double CalculateAveragePrice() const;
  std::string isbn_;
  unsigned units_sold_;
  double revenue_;
};

SalesData Add(const SalesData &lhs, const SalesData &rhs);
std::istream &Read(std::istream &is, SalesData &data);
#endif	//CPP_PRIMER_CHAPTER7_SALES_DATA_H_