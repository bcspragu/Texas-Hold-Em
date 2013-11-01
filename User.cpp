#include <iostream>
#include "User.h"
#include "Deck.h"

using std::cout;
using std::cin;
using std::endl;

User::User(int startingAmount) : Player(startingAmount){
  wallet = startingAmount;
}
