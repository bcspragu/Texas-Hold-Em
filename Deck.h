#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
  public:
    Deck();
    ~Deck(void);
    std::vector<Card> cards;
    void shuffle();
};

#endif