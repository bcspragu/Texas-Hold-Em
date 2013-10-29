#ifndef USER_H
#define USER_H

#include "Player.h"

class User: public Player {
  public:
    string lastMove;
    User(int startingAmount);
    string getMove(Dealer* d);
    int getAmountForMove(Dealer* d);
};

#endif
