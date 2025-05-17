// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h
#include "card.h"

Card::Card(char s, char v) : suit(s), val(v) {}

char Card::getSuit() const {
    return suit;
}

char Card::getVal() const {
    return val;
}

std::string Card::toString() const {
    return std::string(1, suit) + " " + std::string(1, val);
}

int suitRank(char s) {
    switch (s) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
        default: return -1;
    }
}

int valueRank(char v) {
    switch (v) {
        case 'a': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 't': return 10;
        case 'j': return 11;
        case 'q': return 12;
        case 'k': return 13;
        default: return -1;
    }
}

bool Card::operator<(const Card& other) const {
    if (suit != other.suit)
        return suitRank(suit) < suitRank(other.suit);
    return valueRank(val) < valueRank(other.val);
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && val == other.val;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    std::string valStr = (c.getVal() == 't') ? "10" : std::string(1, c.getVal());
    os << c.getSuit() << " " << valStr;
    return os;
}
