#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"
#include "Move.h"

class Dealer;

class Player {
  public:
    Player(int startingAmount);
    std::vector<Card> hand;
    int wallet;
    virtual Move getMove(Dealer* d);
    virtual int getAmountForMove(Dealer* d);
    Move moveFromString(string moveStr);
};

#endif
