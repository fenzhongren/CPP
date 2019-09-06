#ifndef CPP_PRIMER_QUOTE_QUOTE_H_
#define CPP_PRIMER_QUOTE_QUOTE_H_

#include <string>
#include <iostream>
#include <memory>
#include <utility>

class Quote
{
public:
  using SPtr = std::shared_ptr<Quote>;

  Quote() = delete;
  Quote(const std::string &isbn, double price): isbn_(isbn), price_(price)
  {}

  Quote(const Quote &rhs): isbn_(rhs.isbn_), price_(rhs.price_)
  {
    std::cout << "Enter Quote's copy constructor"
     << std::endl;
  }

  Quote &operator=(const Quote &rhs)
  {
    std::cout << "Enter Quote's operator=&" << std::endl;
    isbn_ = rhs.isbn_;
    price_ = rhs.price_;
    return *this;
  }

  Quote(Quote &&rrhs): isbn_(rrhs.isbn_), price_(rrhs.price_)
  {
    std::cout << "Enter Quote's move constructor"
     << std::endl;
  }

  Quote &operator=(const Quote &&rrhs)
  {
    std::cout << "Enter Quote's operator=&&" << std::endl;
    isbn_ = rrhs.isbn_;
    price_ = rrhs.price_;
    return *this;
  }

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

  virtual Quote *Clone() const &
  {
    std::cout << "Enter Quote's lvalue clone" << std::endl;
    return new Quote(*this);
  }

  virtual Quote *Clone() &&
  {
    std::cout << "Enter Quote's rvalue clone" << std::endl;
    return new Quote(std::move(*this));
  }

private:
  std::string isbn_;
  double price_;
};

class DiscountQuote: public Quote
{
public:
  DiscountQuote() = delete;
  DiscountQuote(const std::string &isbn, double price, std::size_t quantity,
   double discount): Quote(isbn, price), quantity_(quantity),
    discount_(discount)
  {}

  DiscountQuote(const DiscountQuote &rhs): Quote(rhs), quantity_(rhs.quantity_),
   discount_(rhs.discount_)
  {
    std::cout << "Enter DiscountQuote's copy constructor"
     << std::endl;
  }

  DiscountQuote &operator=(const DiscountQuote &rhs)
  {
    std::cout << "Enter DiscountQuote's operator=&" << std::endl;
    Quote::operator=(rhs);
    quantity_ = rhs.quantity_;
    discount_ = rhs.discount_;

    return *this;
  }

  DiscountQuote(DiscountQuote &&rrhs): Quote(std::move(rrhs)),
   quantity_(rrhs.quantity_), discount_(rrhs.discount_)
  {
    std::cout << "Enter DiscountQuote's move constructor"
     << std::endl;
  }

  DiscountQuote &operator=(DiscountQuote &&rrhs)
  {
    std::cout << "Enter DiscountQuote's operator=&&" << std::endl;
    Quote::operator=(std::move(rrhs));
    quantity_ = rrhs.quantity_;
    discount_ = rrhs.discount_;    
  }

  virtual ~DiscountQuote() = default;

  virtual double NetPrice(std::size_t n) const = 0;

  virtual std::ostream &Debug(std::ostream &os) const override
  {
    Quote::Debug(os) << "Quantity: " << quantity_ << " Discount: " << discount_
     << std::endl;
     return os;
  }

protected:
  std::size_t quantity_;
  double discount_;
};

class BulkQuote: public DiscountQuote
{
public:
  BulkQuote() = delete;
  BulkQuote(const std::string &isbn, double price, std::size_t quantity,
   double discount): DiscountQuote(isbn, price, quantity, discount)
  {}

  BulkQuote(const BulkQuote &rhs): DiscountQuote(rhs)
  {
    std::cout << "Enter BulkQuote's copy constructor"
     << std::endl;
  }

  BulkQuote &operator=(const BulkQuote &rhs)
  {
    std::cout << "Enter BulkQuote's operator=&" << std::endl;
    DiscountQuote::operator=(rhs);

    return *this;
  }

  BulkQuote(BulkQuote &&rrhs): DiscountQuote(std::move(rrhs))
  {
    std::cout << "Enter BulkQuote's move constructor"
     << std::endl;
  }

  BulkQuote &operator=(BulkQuote &&rrhs)
  {
    std::cout << "Enter BulkQuote's operator=&&" << std::endl;
    DiscountQuote::operator=(std::move(rrhs));
    return *this;
  }

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

  virtual BulkQuote *Clone() const &
  {
    std::cout << "Enter BulkQuote's lvalue clone" << std::endl;
    return new BulkQuote(*this);
  }

  virtual BulkQuote *Clone() &&
  {
    std::cout << "Enter BulkQuote's rvalue clone" << std::endl;
    return new BulkQuote(std::move(*this));
  }

};

class LimitedQuote: public DiscountQuote
{
public:
  LimitedQuote() = delete;
  LimitedQuote(const std::string &isbn, double price, std::size_t quantity,
   double discount): DiscountQuote(isbn, price, quantity, discount)
  {}

  LimitedQuote(const LimitedQuote &rhs): DiscountQuote(rhs)
  {
    std::cout << "Enter LimitedQuote's copy constructor"
     << std::endl;
  }

  LimitedQuote &operator=(const LimitedQuote &rhs)
  {
    std::cout << "Enter LimitedQuote's operator=&" << std::endl;
    DiscountQuote::operator=(rhs);

    return *this;
  }

  LimitedQuote(LimitedQuote &&rrhs): DiscountQuote(std::move(rrhs))
  {
    std::cout << "Enter LimitedQuote's move constructor"
     << std::endl;
  }

  LimitedQuote &operator=(LimitedQuote &&rrhs)
  {
    std::cout << "Enter LimitedQuote's operator=&&" << std::endl;
    DiscountQuote::operator=(std::move(rrhs));
    return *this;
  }

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

  virtual LimitedQuote *Clone() const &
  {
    std::cout << "Enter LimitedQuote's lvalue clone" << std::endl;
    return new LimitedQuote(*this);
  }

  virtual LimitedQuote *Clone() &&
  {
    std::cout << "Enter LimitedQuote's rvalue clone" << std::endl;
    return new LimitedQuote(std::move(*this));
  }

};

inline double PrintTotal(std::ostream &os, const Quote &item, std::size_t n)
{
  double ret = item.NetPrice(n);
  os << "ISBN: " << item.get_isbn() << " # sold: " << n << " total due: " <<
   ret << std::endl;

  return ret;
}

#endif  //CPP_PRIMER_QUOTE_QUOTE_H_