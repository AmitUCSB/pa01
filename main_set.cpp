// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <iterator>
#include "card.h"

using namespace std;

void playGame(set<Card>& p1, set<Card>& p2) {
  bool foundMatch = true;

  while (foundMatch) {
    foundMatch = false;

    // Alice's turn (forward order)
    for (auto it = p1.begin(); it != p1.end(); ) {
      if (p2.find(*it) != p2.end()) {
        cout << "Alice picked matching card " << *it << endl;
        p2.erase(*it);
        it = p1.erase(it);  // erase returns next valid iterator
        foundMatch = true;
        break;
      } else {
        ++it;
      }
    }

    // Bob's turn (reverse order)
    for (auto it = p2.rbegin(); it != p2.rend(); ++it) {
      if (p1.find(*it) != p1.end()) {
        cout << "Bob picked matching card " << *it << endl;
        p1.erase(*it);
        auto fwdIt = std::prev(it.base()); // convert reverse to forward iterator
        p2.erase(fwdIt); // safe erase
        foundMatch = true;
        break;
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

  while (getline(cardFile1, line) && !line.empty()) {
    istringstream iss(line);
    string valStr;
    char suit, val;
    iss >> suit >> valStr;
    val = (valStr == "10") ? 't' : valStr[0];
    p1.insert(Card(suit, val));
  }
  cardFile1.close();

  while (getline(cardFile2, line) && !line.empty()) {
    istringstream iss(line);
    string valStr;
    char suit, val;
    iss >> suit >> valStr;
    val = (valStr == "10") ? 't' : valStr[0];
    p2.insert(Card(suit, val));
  }
  cardFile2.close();

  playGame(p1, p2);

  return 0;
}
