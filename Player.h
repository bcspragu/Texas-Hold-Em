#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class Player {
  public:
    std::vector<Card> hand;
    int wallet;
    int scoreHand();
    bool bet(int amount);
    bool raise(int amount);
    bool check();
    bool call();
    bool fold();
    bool allIn();
};

#endif
