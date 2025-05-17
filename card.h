// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
public:
    Card(char suit, char value);

    char getSuit() const;
    char getVal() const;
    std::string toString() const;

    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);

private:
    char suit; 
    char val;  
};

#endif
