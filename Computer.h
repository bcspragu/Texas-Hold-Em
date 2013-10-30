#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <map>
#include <algorithm>
#include "Card.h"
#include "Deck.h"
#include "SuitValue.h"
#include "Player.h"
#include "Table.h"

enum pocketRate {HORRIBLE, BAD, QUESTIONABLE, OK, GOOD, GREAT};

class Dealer;
class Computer: public Player {
  public:
    Computer(int startingAmount);
    static int ratePocketCards(std::vector<Card> hand);

    Move getMove(Dealer* d);
    int getAmountForMove(Dealer* d);    
    int getRaiseAmount(Dealer* d);
    static int getDecision(int handValue);
    int raiseAmount;
    int move;
    bool alreadyFolded;
    int handValue;
};

#endif
