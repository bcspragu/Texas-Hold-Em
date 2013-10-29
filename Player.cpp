#include "Player.h"
#include <assert.h>

Player::Player(int startingAmount){
  wallet = startingAmount;
}

string Player::getMove(Dealer* d){
  printf("getMove called on base Player class\n");
  assert(false);
};

int Player::getAmountForMove(Dealer* d){
  printf("getMove called on base Player class\n");
  assert(false);
};