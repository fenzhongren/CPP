#include "book.h"
#include <list>

std::ostream &operator<<(std::ostream &os, const Book &book)
{
  os << book.id_  << " " << book.price_ << " " << book.name_;
  return os;
}

std::istream &operator>>(std::istream &is, Book &book)
{
  is >> book.id_ >> book.price_ >> book.name_;
  return is;
}

std::vector<Book::SPtr> BookRepository::Query(ISpecification<Book::SPtr>::SPtr spec_sptr)
{
  std::vector<Book::SPtr> temp;
  for(auto it = book_map_.begin(); it != book_map_.end(); ++it) {
    if(spec_sptr->IsSatisfiedBy(it->second)) {
      temp.push_back(it->second);
    }
  }
  return temp;
}

void BookRepository::Remove(ISpecification<Book::SPtr>::SPtr spec_sptr)
{
  std::list<int> need_to_remove;
  for(auto it = book_map_.begin(); it != book_map_.end(); ++it) {
    if(spec_sptr->IsSatisfiedBy(it->second)) {
      need_to_remove.push_back(it->first);
    }
  }

  for(auto key: need_to_remove) {
    //std::cout << "Removing " << key << std::endl;
    book_map_.erase(key);
  }
}