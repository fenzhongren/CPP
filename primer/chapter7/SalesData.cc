#include "SalesData.h"

#include <iostream>

SalesData::SalesData(std::istream & is)
{
  Read(is, *this);
}

void SalesData::SetSalesData(const std::string & isbn, unsigned units_sold, double revenue)
{
  isbn_ = isbn;
  units_sold_ = units_sold;
  revenue_ = revenue;
}

SalesData & SalesData::Combine(const SalesData & rhs)
{
	// TODO: insert return statement here
  units_sold_ += rhs.units_sold_;
  revenue_ += rhs.revenue_;
  return *this;
}

double SalesData::CalculateAveragePrice() const
{
  double average_price = 0;
  if(units_sold_ > 0) {
    average_price = revenue_ / units_sold_;
  }

  return average_price;
}

SalesData Add(const SalesData & lhs, const SalesData & rhs)
{
  SalesData sum(lhs);
  sum.Combine(rhs);
  return sum;
}

std::istream & Read(std::istream & is, SalesData & data)
{
	// TODO: insert return statement here
  std::string isbn;
  unsigned units_sold;
  double price;
  double revenue;

  is >> isbn >> units_sold >> price;
  revenue = units_sold * price;
  data.SetSalesData(isbn, units_sold, revenue);

  return is;
}

std::ostream & Print(std::ostream & os, const SalesData & data)
{
	// TODO: insert return statement here
  os << data.get_isbn() << " " << data.units_sold_ << " "
    << data.revenue_ << " " << data.CalculateAveragePrice();

  return os;
}
