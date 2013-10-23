#ifndef CARD_H
#define CARD_H

#include "SuitValue.h"

class Card {
  public:
    Card(Suit s, Value v);
    ~Card(void);
    Suit suit;
    Value value;
    static Suit suitFromInt(int i);
    static Value valueFromInt(int i);
};

#endif
