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
  std:string name_;
};

std::istream &operator>>(std::istream &is, BookParameter &book)
{
  is >> book.id_ >> book.price_ >> book.name_;
  return is;
}

int main()
{
  BookRepository book_repository;

  ifstream is("./book.txt");
  BookParameter temp;
  while(is >> temp) {
    book_repository.Add(make_shared<Book>(temp.id_, temp.price_, temp.name_));
  }

  auto specification_all  = make_shared<BookSpecificationByAll>();
  auto books = book_repository.Query(specification_all);

  for(auto book: books) {
    cout << book << endl;
  }

  return 0;
}