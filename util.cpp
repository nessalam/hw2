#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> output;
  string temp = ""; //temp string to build individual owrds

  //iterate thru given words
  for(size_t i = 0; i < rawWords.size(); i++){
    char currentChar = rawWords[i];
    //checking if char is alphanumeric or not
    if(isalnum(currentChar)){
      //making char commoncase lowercase or wahtever
      currentChar = tolower(currentChar);
      //adding to string bc we're building it char by char <- cuts off if space or punctuation iykwim
      temp += currentChar;
    }
    //space or punctuation
    else{
      //making sure longer than 2 char
      if(temp.length() >= 2){
        output.insert(temp); //inserting into output set
      }
      temp = ""; //resetting so we can build next individual word
    }
  }

  //checking and inserting last word
  if(temp.length() >= 2){
    output.insert(temp);
  }
  return output;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
