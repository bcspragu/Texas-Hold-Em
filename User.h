#ifndef USER_H
#define USER_H

#include "Player.h"

class User: public Player {
  public:
    User(int startingAmount);
    Move getMove(Dealer* d);
    int getAmountForMove(Dealer* d);
};

#endif
