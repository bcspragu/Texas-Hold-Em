#ifndef TABLE_H
#define TABLE_H

#include "Move.h"
#include "display.h"

//class display;
class Dealer;

class Table {
  public:
  	display gameDisplay;
    void drawBoard(Dealer* d);
    Move getUserMove();
    int getUserValue();
};

#endif