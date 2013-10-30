#ifndef TABLE_H
#define TABLE_H

#include "Move.h"
class Dealer;

class Table {
  public:
    Table();
    ~Table(void);
    void drawBoard(Dealer* d);
    Move getUserMove();
    int getUserValue();
};

#endif