// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include "card.h"

using namespace std;

void playGame(set<Card>& p1, set<Card>& p2) {
  bool foundMatch = true;

  while (foundMatch) {
    foundMatch = false;

    for (auto it = p1.begin(); it != p1.end(); ) {
      if (p2.find(*it) != p2.end()) {
        cout << "Alice picked matching card " << *it << endl;
        p2.erase(*it);
        it = p1.erase(it);
        foundMatch = true;
        break;
      } else {
        ++it;
      }
    }

    for (auto it = p2.rbegin(); it != p2.rend(); ) {
      if (p1.find(*it) != p1.end()) {
        cout << "Bob picked matching card " << *it << endl;
        p1.erase(*it);
        auto fwdIt = next(it).base(); 
        p2.erase(fwdIt);
        foundMatch = true;
        break;
      } else {
        ++it;
      }
    }
  }

  cout << "\nAlice's cards:" << endl;
  for (const Card& c : p1) {
    cout << c << endl;
  }

  cout << "\nBob's cards:" << endl;
  for (const Card& c : p2) {
    cout << c << endl;
  }
}

int main(int argc, char** argv) {
  if (argc < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argv[1]);
  ifstream cardFile2(argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file(s)." << endl;
    return 1;
  }

  set<Card> p1;
  set<Card> p2;
  char val;
  char suit;

  while (getline(cardFile1, line) && !line.empty()) {
    istringstream iss(line);
    iss >> suit >> val;
    p1.insert(Card(suit, val));
  }
  cardFile1.close();

  while (getline(cardFile2, line) && !line.empty()) {
    istringstream iss(line);
    iss >> suit >> val;
    p2.insert(Card(suit, val));
  }
  cardFile2.close();

  playGame(p1, p2);

  return 0;
}
