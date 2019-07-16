#include "book.h"

std::ostream &operator<<(std::ostream &os, const Book &book)
{
  os << book.id_ << book.price_ << book.name_;
  return os;
}

std::istream &operator>>(std::istream &is, Book &book)
{
  is >> book.id_ >> book.price_ >> book.name_;
  return is;
}

std::vector<Book::SPtr> BookRepository::Query(ISpecification::SPtr spec_sptr)
{
  vector<Book::SPtr> temp;
  for(auto it = book_map_.cbegin(); it != bool_map_.cend(); ++it){
    if(spec_sptr->IsSatisfiedBy(it->second()))
    temp.push_back(it->second());
  }
  return temp;
}