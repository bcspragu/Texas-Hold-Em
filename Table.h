#ifndef TABLE_H
#define TABLE_H

#include "Move.h"
class Dealer;

class Table {
  public:
    void drawBoard(Dealer* d);
    Move getUserMove();
    int getUserValue();
};

#endif