#include "clothing.h"
#include "util.h"
#include <iostream>
#include <sstream>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, 
const std::string brand) : Product(category, name, price, qty){
  size_ = size;
  brand_ = brand;
}

std::set<std::string> Clothing::keywords() const{
  //std::set<std::string> foundWords;
  //split punctuation, gives us individual words
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(brand_);

  //loops thru names n adds to our found words set
  /*for(std::set<std::string>:: iterator it = nameWords.begin(); it!= nameWords.end(); ++it){
    foundWords.insert(*it);
  }
  //same but brands name
  for(std::set<std::string>:: iterator it = brandWords.begin(); it!= brandWords.end(); ++it){
    foundWords.insert(*it);
  }
  
  return foundWords;*/
  return setUnion(nameWords, brandWords);
}

std::string Clothing::displayString() const{
  std::string printAll;
  
  printAll = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n";
  std::stringstream numString;
  numString << price_;
  printAll += numString.str() + " " + std::to_string(qty_) + " left.";
  return printAll;
}

void Clothing::dump(std::ostream &os) const{
  //os << category_ << "\n" << name_ << "\n" << std::to_string(price_) << "\n" << std::to_string(qty_) << "\n" << size_ << "\n" << brand_ << std::endl;
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n"; 
  os << size_ << "\n";
  os << brand_ << "\n";
}

Clothing::~Clothing(){}