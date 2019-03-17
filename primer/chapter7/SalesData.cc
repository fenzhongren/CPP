#include "SalesData.h"

#include <iostream>

void SalesData::setSalesData(const std::string & isbn, unsigned units_sold, double revenue)
{
  isbn_ = isbn;
  units_sold_ = units_sold;
  revenue_ = revenue;
}

SalesData & SalesData::combine(const SalesData & rhs)
{
	// TODO: insert return statement here
  units_sold_ += rhs.units_sold_;
  revenue_ += rhs.revenue_;
}

SalesData Add(const SalesData & lhs, const SalesData & rhs)
{
  SalesData temp(lhs);
  temp.combine(rhs);
  return temp;
}

std::istream & Read(std::istream & stream, SalesData & data)
{
	// TODO: insert return statement here
  std::string isbn;
  unsigned units_sold;
  double revenue;
  stream >> isbn >> units_sold >> revenue;
  data.setSalesData(isbn, units_sold, revenue);
  return stream;
}

std::ostream & Print(std::ostream & stream, const SalesData & data)
{
	// TODO: insert return statement here
}
