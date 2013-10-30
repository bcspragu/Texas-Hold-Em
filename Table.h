#ifndef TABLE_H
#define TABLE_H

#include "Move.h"
#include "display.h"
#include "Dealer.h"
#include "Player.h"

//class display;

class Table {
  public:
  	display gameDisplay;
    void drawBoard(Dealer* d);
    Move getUserMove();
    int getUserValue();
};

#endif