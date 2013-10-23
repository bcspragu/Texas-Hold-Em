#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

class Player {
  public:
    Player();
    ~Player(void);
    Card hand[];
    int wallet;
};

#endif
