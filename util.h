#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2) 
{ //finding the same elements between both
  std::set<T>output;

  //one for each set so we can compare each element
  typename std::set<T>::iterator it;
  typename std::set<T>::iterator it2;
  it = s1.begin();
  it2 = s2.begin();

  while(it != s1.end() && it2 != s2.end()){
    if(*it < *it2){
      //if true, set 1 has a diff element so no intersection, increment
      ++it;
    }
    else if(*it2 < *it){
      ++it2;
    }
    else{
      //value same so we add one of them
      output.insert(*it);
      ++it;
      ++it2;
    }
  }
  return output;
}  

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{ //showing all the stuff in both sets but no duplicates, basically listing what both sets have
  std::set<T>output;

  //one for each set so we can compare each element
  typename std::set<T>::iterator it;
  typename std::set<T>::iterator it2;
  it = s1.begin();
  it2 = s2.begin();

  //go thru both and compare while incrementing smaller one (bc sets are ordered smallest to largest)
  while(it != s1.end() && it2 != s2.end()){
    if(*it < *it2){
      //true means set 1 has the element but set 2 doesnt so we add then increment
      output.insert(*it);
      ++it;
    }
    else if (*it2 < *it){
      output.insert(*it2);
      ++it2;
    }
    else{
      //same element in both set, only add one and increment both
      output.insert(*it);
      ++it;
      ++it2;
    }
  }
  //just to be sure add whatever elements left if we still haven't reached the end
  while(it != s1.end()){
    output.insert(*it);
    ++it;
  }
  while(it2 != s2.end()){
    output.insert(*it2);
    ++it2;
  }
  return output;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
