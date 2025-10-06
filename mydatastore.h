#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>
#include <queue>
#include <vector>
#include <set>

class MyDataStore : public DataStore{
public:
  MyDataStore();
  ~MyDataStore();

  //from datastore.h
  void addProduct(Product* p) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>&terms, int type) override;
  void dump(std::ostream& ofile) override;

  //diy functions for store
  void addCart(std::string username, int hitIndex);
  void viewCart(std::string username);
  void buyCart(std:: string username);

private:
  //store all products
  std::vector<Product*> products_;
  //store all users
  std::vector<User*> users_;

  //mapping usernames to objects
  std::map<std::string, User*> userMap_;
  //maping keywords to the products w the word
  std::map<std::string, std::set<Product*>> wordIndex_;

  //store user's carts - each cart = a queue of products
  std::map<std::string, std::queue<Product*>> userCarts_;
  
  //tracks last search results so we can add
  std::vector<Product*> lastSearch_;
};

#endif