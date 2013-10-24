#ifndef CARD_H
#define CARD_H

#include <string>
#include "SuitValue.h"

using std::string;

class Card {
  public:
    Card(Suit s, Value v);
    ~Card(void);
    Suit suit;
    Value value;
    static Suit suitFromInt(int i);
    static Value valueFromInt(int i);
    string cardString();
    bool operator<(const Card &other) const;
};

#endif
