#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <sstream>

using namespace std;

MyDataStore::MyDataStore(){}
MyDataStore::~MyDataStore(){
  //delete products
  for(unsigned int i=0; i < products_.size(); i++){
    delete products_[i];
  }

  //deelte users
  for(unsigned int i=0; i < users_.size(); i++){
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product* p){
  //adds to product list
  products_.push_back(p);

  //getting keywords from the product
  set<string>keywords = p->keywords();

  //adding to keywrod index
  for(set<string>::iterator it = keywords.begin(); it!=keywords.end(); ++it){
    string keyword = convToLower(*it);
    //if the keyword isnt in the map yet, add it
    if(wordIndex_.find(keyword) == wordIndex_.end()){
      set<Product*> newSet;
      newSet.insert(p);
      wordIndex_[keyword] = newSet;
    }
    else{
      //keyword already in map, add to current set
      wordIndex_[keyword].insert(p);
    }
  }
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  string lowerUser = convToLower(u->getName());
  userMap_[lowerUser] = u;

  //initialize the empty cart for curr user
  queue<Product*> emptyCart;
  userCarts_[lowerUser] = emptyCart;
}

vector<Product*> MyDataStore:: search(vector<string>& terms, int type){
  vector<Product*> output;

  if(terms.empty()){
    lastSearch_ = output; //storing empty outputs
    return output;
  }

  set<Product*> prodSet;

  if(type==0){ //AND search method
    //start w products that match w first keyword first
    string firstTerm = convToLower(terms[0]);
    if(wordIndex_.find(firstTerm) != wordIndex_.end()){
      prodSet = wordIndex_[firstTerm];
    }
    else{
      //if first term not found, no prods match in our AND search
      lastSearch_ = output;
      return output;
    }

    //for AND search, use intersect func for additional keywords
    for(unsigned int i = 1; i < terms.size(); i++){
      string currTerm = convToLower(terms[i]);
      if(wordIndex_.find(currTerm) != wordIndex_.end()){
        set<Product*> termProds = wordIndex_[currTerm];
        prodSet = setIntersection(prodSet, termProds);
      }
      else{
        //no terms found = no prods match our AND search
        prodSet.clear();
        break; 
      }
    }
  }
  else{ //OR search method
    //setUnion func to match any terms bc its OR
    for(unsigned int i = 0; i < terms.size(); i++){
      string currTerm = convToLower(terms[i]);
      if(wordIndex_.find(currTerm) != wordIndex_.end()){
        set<Product*> termProds = wordIndex_[currTerm];
        prodSet = setUnion(prodSet, termProds);
      }
    }
  }
  //converting set into vector to return
  for(set<Product*>::iterator it = prodSet.begin(); it!=prodSet.end(); ++it){
    output.push_back(*it);
  }
  //store the last search for our adding to cart
  lastSearch_ = output;
  return output;
}

void MyDataStore::dump(ostream& ofile){
  ofile << "<products>" << endl;
  for(unsigned int i =0; i < products_.size(); i++){
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for(unsigned int i =0; i < users_.size(); i++){
    ofile << users_[i]->getName() << " ";
    ofile << users_[i]->getBalance() << " ";
    ofile << users_[i]->getType() << endl;
  }
  ofile << "</users>" << endl;
}

void MyDataStore::addCart(string username, int hitIndex){
  //convert to common case 
  string lowerUser = convToLower(username);

  //check if user exists
  if(userMap_.find(lowerUser) == userMap_.end()){
    cout << "Invalid request" << endl;
    return;
  }

  //check if our index is valid
  if(hitIndex < 1 || hitIndex > (int)lastSearch_.size()){
    cout << "Invalid request" << endl;
    return;
  }

  //get product w index
  Product* prodToAdd = lastSearch_[hitIndex - 1];

  //add to user's cart
  userCarts_[lowerUser].push(prodToAdd);
  cout << "Product added." << endl;
}

void MyDataStore::viewCart(string username){
  //convert to common case 
  string lowerUser = convToLower(username);

  //check if user exists
  if(userMap_.find(lowerUser) == userMap_.end()){
    cout << "Invalid username" << endl;
    return;
  }
  queue<Product*> userCart = userCarts_[lowerUser];

  //temp cart to display items bc queue doesnt let us iterate
  queue<Product*> temp = userCart;
  int itemNum = 1;

  if(temp.empty()){
    cout << "Cart is empty." << endl;
    return;
  }
  while(!temp.empty()){
    Product* p = temp.front();
    temp.pop();
    cout << "Item " << itemNum << std::endl;
    cout << p->displayString() << endl;
    cout << endl;
    itemNum++;
  }
}

void MyDataStore::buyCart(string username){
  //convert to common case 
  string lowerUser = convToLower(username);

  //check if user exists
  if(userMap_.find(lowerUser) == userMap_.end()){
    cout << "Invalid username" << endl;
    return;
  }

  User* user = userMap_[lowerUser];
  queue<Product*>& userCart = userCarts_[lowerUser];

  //temp queue to hold items we keep
  queue<Product*> newCart;

  while(!userCart.empty()){
    Product* p = userCart.front();
    userCart.pop();

    //check if we can even buy the item </3
    if(p->getQty() > 0 && user->getBalance() >= p->getPrice()){
      //if we can buy it, reduce qty n balance
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    }
    else{
      //not enough money, keep in cart
      newCart.push(p);
    }
  }
  //replace old cart w new cart (that has unpurchased stuff too)
  userCarts_[lowerUser] = newCart;
}