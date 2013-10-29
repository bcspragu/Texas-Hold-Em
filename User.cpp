#include <iostream>
#include "User.h"
#include "Deck.h"

using std::cout;
using std::cin;
using std::endl;

User::User(int startingAmount){
  wallet = startingAmount;
}

// have the user enter their move, store it for later
string User::getMove(Dealer* d){
  // call out to display class to display options to user
  // display class will return button pressed
  string choice;
  cout << "Your cards: " << Deck::displayHand(hand) << endl;
  cout << "Your choice: ";
  cin >> choice;
  lastMove = choice;
  return choice;
}

// have the user enter the amount to bet/raise
int User::getAmountForMove(Dealer* d){
  int amount;
  cout << lastMove << " amount: ";
  cin >> amount;
  return amount;
}
