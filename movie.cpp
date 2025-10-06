#include "movie.h"
#include "util.h"
#include <iostream>
#include <sstream>

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, 
const std::string rating) : Product(category, name, price, qty){
  genre_ = genre;
  rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
  std::set<std::string> foundWords;
  //no need to parse genre, add whole string later
  std::set<std::string> nameWords = parseStringToWords(name_);
  for(std::set<std::string>::iterator it = nameWords.begin(); it!= nameWords.end(); it++){
    foundWords.insert(*it);
  }
  foundWords.insert(genre_);

  return foundWords;
}

std::string Movie::displayString() const{
  std::string printAll;
  
  printAll = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n";
  std::stringstream numString;
  numString << price_;
  printAll += numString.str() + " " + std::to_string(qty_) + " left.";
  return printAll;
}

void Movie::dump(std::ostream &os) const{
  //os << category_ << "\n" << name_ << "\n" << std::to_string(price_) << "\n" << std::to_string(qty_) << "\n" << genre_ << "\n" << rating_ << std::endl;
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n"; 
  os << genre_ << "\n";
  os << rating_ << "\n";
}

Movie::~Movie(){}