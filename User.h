#ifndef USER_H
#define USER_H

#include "Player.h"
#include "Dealer.h"

class User: public Player {
  public:
    User(int startingAmount);
};

#endif
