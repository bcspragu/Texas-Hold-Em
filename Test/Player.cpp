#include "Player.h"
#include <assert.h>

void Player::updateWallet(){
  const char* move = lastMove.c_str();
  char money[10];
  switch(ID){
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
  }
}
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
