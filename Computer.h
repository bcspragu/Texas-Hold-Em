#ifndef COMPUTER_H
#define COMPUTER_H



#include <vector>
#include "Card.h"
#include "Deck.h"
#include "SuitValue.h"
#include "Dealer.h"
#include "Player.h"
#include "Table.h"
#include <map>
#include <algorithm>

enum pocketRate {HORRIBLE, BAD, QUESTIONABLE, OK, GOOD, GREAT};


class Computer: public Player {
  public:
    Computer(int startingAmount);

    static int ratePocketCards(std::vector<Card> hand);
   
};




#endif
