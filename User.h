#ifndef USER_H
#define USER_H

#include "Player.h"

class User: public Player {
  public:
    string lastMove;
    User(int startingAmount);
    virtual Move getMove(Dealer* d);
    virtual int getAmountForMove(Dealer* d);
};

#endif
