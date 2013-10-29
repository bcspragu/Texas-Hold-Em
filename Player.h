#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class Dealer;

class Player {
  public:
    std::vector<Card> hand;
    int wallet;
    string getMove(Dealer* d);
    int getAmountForMove(Dealer* d);
};

#endif
