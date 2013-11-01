#include "Player.h"
#include <assert.h>

Player::Player(int startingAmount){
  wallet = startingAmount;
  lastMove = "Waiting";
}

Move Player::getMove(Dealer* d){
  assert(false);
};

int Player::getAmountForMove(Dealer* d){
  assert(false);
};
