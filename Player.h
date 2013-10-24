#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class Player {
  public:
    Player();
    ~Player(void);
    std::vector<Card> hand;
    int wallet;
};

#endif
