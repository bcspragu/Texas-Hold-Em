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
    Move getMove(Dealer* d);
    int getAmountForMove(Dealer* d);
    Move moveFromString(string moveStr);
};

#endif
