#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

using namespace std;

class Deck {
  public:
    Deck();
    ~Deck(void);
    vector<Card> cards;
    void shuffle();
};

#endif
