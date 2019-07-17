#include "book.h"

#include <iostream>
#include <fstream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::make_shared;

struct BookParameter
{
  int id_;
  double price_;
  std::string name_;
};

std::istream &operator>>(std::istream &is, BookParameter &book)
{
  is >> book.id_ >> book.price_ >> book.name_;
  return is;
}

std::ostream &operator<<(std::ostream &os, const BookParameter &book)
{
  os << book.id_ << " " << book.price_  << " " << book.name_;
  return os;
}

int main()
{
  BookRepository book_repository;

  ifstream is("./book.txt");
  BookParameter temp;
  while(is >> temp) {
    //cout << temp << endl;
    book_repository.Add(make_shared<Book>(temp.id_, temp.price_, temp.name_));
  }

  auto specification1  = make_shared<BookSpecificationByPriceGreaterThan>(30.0);
  auto specification2  = make_shared<BookSpecificationByPriceLessThan>(50);
  auto specification3  = make_shared<BookSpecificationByName>("aaa");
  auto books = book_repository.Query(specification1->And(specification2)->Or(specification3));

  for(auto book: books) {
    cout << *book << endl;
  }

  return 0;
}