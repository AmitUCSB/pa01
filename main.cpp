// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include "card_list.h"
#include "card.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  card_list alice;
  card_list bob;

  while (getline(cardFile1, line) && (line.length() > 0)) {
    istringstream iss(line);
    char suit;
    string valStr;
    iss >> suit >> valStr;
    char val;
    if (valStr == "10") val = 't';
    else val = valStr[0];
    Card c(suit, val);
    alice.insert(c);
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
    istringstream iss(line);
    char suit;
    string valStr;
    iss >> suit >> valStr;
    char val;
    if (valStr == "10") val = 't';
    else val = valStr[0];
    Card c(suit, val);
    bob.insert(c);
  }
  cardFile2.close();

  playGame(alice, bob);

  return 0;
}
