#include <iostream>
#include "User.h"
#include "Deck.h"

using std::cout;
using std::cin;
using std::endl;

User::User(int startingAmount) : Player(startingAmount){
  wallet = startingAmount;
  lastMove = "starting game";
}

// have the user enter their move, store it for later
Move User::getMove(Dealer* d){
  // display class will return button pressed
  // "raise", "call", "fold", "allin"

  string choice;
  cout << "Your wallet: $" << wallet << endl;
  cout << "Your cards: " << Deck::displayHand(hand) << endl;
  cout << "Your choice: ";
  cin >> choice;
  lastMove = choice;
  return moveFromString(choice);
}

// have the user enter the amount to raise
int User::getAmountForMove(Dealer* d){
  int amount;
  cout << lastMove << " amount: ";
  cin >> amount;
  return amount;
}

