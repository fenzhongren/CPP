#ifndef CPP_PRIMER_QUOTE_QUOTE_H_
#define CPP_PRIMER_QUOTE_QUOTE_H_

#include <string>
#include <iostream>

class Quote
{
public:
  Quote() = delete;
  Quote(const std::string &isbn, double price): isbn_(isbn), price_(price)
  {}

  virtual ~Quote() = default;

  std::string get_isbn() const
  {
    return isbn_;
  }

  double get_price() const
  {
    return price_;
  }

  virtual double NetPrice(std::size_t n) const
  {
    return n * price_;
  }

  virtual std::ostream &Debug(std::ostream &os) const
  {
    os << "ISBN: " << isbn_ << " Price: " << price_ << std::endl;
    return os;
  }

private:
  std::string isbn_;
  double price_;
};

class BulkQuote: public Quote
{
public:
  BulkQuote() = delete;
  BulkQuote(const std::string &isbn, double price, std::size_t quantity,
   double discount): Quote(isbn, price), quantity_(quantity),
    discount_(discount)
  {}

  virtual ~BulkQuote() = default;

  virtual double NetPrice(std::size_t n) const override
  {
    double total = 0;
    double price = get_price();

    if(n > quantity_) {
      total = quantity_ * price + (n - quantity_) * price * discount_;
    } else {
      total = n * price;
    }

    return total;
  }

  virtual std::ostream &Debug(std::ostream &os) const override
  {
    Quote::Debug(os) << "Quantity: " << quantity_ << " Discount: " << discount_
     << std::endl;
     return os;
  } 

private:
  std::size_t quantity_;
  double discount_;
};

class LimitedQuote: public Quote
{
public:
  LimitedQuote() = delete;
  LimitedQuote(const std::string &isbn, double price, std::size_t quantity,
   double discount): Quote(isbn, price), quantity_(quantity),
    discount_(discount)
  {}

  virtual ~LimitedQuote() = default;

  virtual double NetPrice(std::size_t n) const override
  {
    double total = 0;
    double price = get_price();

    if(n <= quantity_) {
      total = n * price * discount_;
    } else {
      total = quantity_ * price * discount_ + (n - quantity_) * price;
    }

    return total;
  }

  virtual std::ostream &Debug(std::ostream &os) const override
  {
    Quote::Debug(os) << "Quantity: " << quantity_ << " Discount: " << discount_
     << std::endl;
     return os;
  }

private:
  std::size_t quantity_;
  double discount_;
};

inline double PrintTotal(std::ostream &os, const Quote &item, std::size_t n)
{
  double ret = item.NetPrice(n);
  os << "ISBN: " << item.get_isbn() << " # sold: " << n << " total due: " <<
   ret << std::endl;

  return ret;
}

#endif  //CPP_PRIMER_QUOTE_QUOTE_H_