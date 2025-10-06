#include "book.h"
#include "util.h"
#include <iostream>
#include <sstream>

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, 
const std::string author) : Product(category, name, price, qty){
  isbn_ = isbn;
  author_ = author;
}

std::set<std::string> Book::keywords() const{
  //std::set<std::string> foundWords;
  //split punctuation, gives us individual words
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(author_);

  //loops thru book names n adds to our found words set
  /*for(std::set<std::string>:: iterator it = nameWords.begin(); it!= nameWords.end(); ++it){
    foundWords.insert(*it);
  }
  //same but authors name
  for(std::set<std::string>:: iterator it = authorWords.begin(); it!= authorWords.end(); ++it){
    foundWords.insert(*it);
  }
  //also adding exact isbn
  foundWords.insert(isbn_);

  return foundWords;*/
  std::set<std::string> foundWords = setUnion(nameWords, authorWords);
  foundWords.insert(isbn_);

  return foundWords;
}

std::string Book::displayString() const{
  std::string printAll;
  
  printAll = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n";
  std::stringstream numString;
  numString << price_;
  printAll += numString.str() + " " + std::to_string(qty_) + " left.";
  return printAll;
}

void Book::dump(std::ostream& os)const{
  //os << category_ << "\n" << name_ << "\n" << std::to_string(price_) << "\n" << std::to_string(qty_) << "\n" << isbn_ << "\n" << author_ << std::endl;
  //cooked formatting
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n"; 
  os << isbn_ << "\n";
  os << author_ << "\n";
}

Book::~Book(){}