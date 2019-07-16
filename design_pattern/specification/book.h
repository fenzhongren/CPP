#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_BOOK_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_BOOK_H_

#include "composite_specification.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

class Book
{
public:
  using SPtr = std::shared_ptr<Book>;
  Book() = delete;
  Book(int id, double price, const std::string name): id_(id), price_(price),
    name_(name)
  {}

  int get_id() const
  {return id_;}

  double get_price() const
  {return price_;}

  std::string get_name() const
  {return name_;}

  virtual ~Book() = default;

  friend std::ostream &operator<<(std::ostream &os, const Book &book);
  friend std::istream &operator>>(std::istream &is, Book &book);

private:
  int id_;
  double price_;
  std::string name_;
};



class BookSpecificationByPrice: public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByPrice() = delete;
  BookSpecificationByPrice(double price): price_(price)
  {}


  virtual bool IsSatisfiedBy(Book::SPtr book_sptr) const
  {return book_sptr->get_price() == price_;} 

  virtual ~BookSpecificationByPrice() = default;
private:
  double price_;
};

class BookSpecificationByAll: public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByAll() = default;

  virtual bool IsSatisfiedBy(Book::SPtr book_sptr) const
  {return true;} 

  virtual ~BookSpecificationByAll() = default;
};

class BookRepository
{
public:
  BookRepository() = default;

  void Add(Book::SPtr b_sptr)
  {book_map_[b_sptr->get_id()] = b_sptr;}

  std::vector<Book::SPtr> Query(ISpecification<Book::SPtr>::SPtr spec_sptr);

private:
  std::map<int, Book::SPtr> book_map_;
};

#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_BOOK_H_