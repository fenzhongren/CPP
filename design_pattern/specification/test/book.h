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

  virtual ~Book()
  {std::cout << "Destory book " << name_ << std::endl;}

  friend std::ostream &operator<<(std::ostream &os, const Book &book);
  friend std::istream &operator>>(std::istream &is, Book &book);

private:
  int id_;
  double price_;
  std::string name_;
};

class BookSpecificationByName: public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByName() = delete;
  BookSpecificationByName(const std::string &name): name_(name)
  {}


  virtual bool IsSatisfiedBy(const Book::SPtr &book_csptr) const
  {return book_csptr->get_name() == name_;} 

  virtual ~BookSpecificationByName() = default;
private:
  std::string name_;
};

class BookSpecificationByPrice: public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByPrice() = delete;
  BookSpecificationByPrice(double price): price_(price)
  {}


  virtual bool IsSatisfiedBy(const Book::SPtr &book_csptr) const
  {return book_csptr->get_price() == price_;} 

  virtual ~BookSpecificationByPrice() = default;
private:
  double price_;
};

class BookSpecificationByPriceGreaterThan:
 public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByPriceGreaterThan() = delete;
  BookSpecificationByPriceGreaterThan(double price): price_(price)
  {}


  virtual bool IsSatisfiedBy(const Book::SPtr &book_csptr) const
  {return book_csptr->get_price() > price_;} 

  virtual ~BookSpecificationByPriceGreaterThan() = default;
private:
  double price_;
};

class BookSpecificationByPriceLessThan:
 public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByPriceLessThan() = delete;
  BookSpecificationByPriceLessThan(double price): price_(price)
  {}


  virtual bool IsSatisfiedBy(const Book::SPtr &book_csptr) const
  {return book_csptr->get_price() < price_;} 

  virtual ~BookSpecificationByPriceLessThan() = default;
private:
  double price_;
};

class BookSpecificationByAll: public CompositeSpecification<Book::SPtr>
{
public:
  BookSpecificationByAll() = default;

  virtual bool IsSatisfiedBy(const Book::SPtr &book_csptr) const
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

  void Remove(ISpecification<Book::SPtr>::SPtr spec_sptr);

private:
  std::map<int, Book::SPtr> book_map_;
};

#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_BOOK_H_