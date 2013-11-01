#include <iostream>
#include "User.h"
#include "Deck.h"
#include "Dealer.h"

using std::cout;
using std::cin;
using std::endl;

User::User(int startingAmount) : Player(startingAmount){
  wallet = startingAmount;
}

int User::getAmountForMove(Dealer* d){
}

Move User::getMove(Dealer* d){
  // display class will return button pressed
  // "raise", "call", "fold", "allin"

  //mvprintw(36,36,"Your Move");

  char potstr[21];
  d->updateValuesOnScreen();
}
