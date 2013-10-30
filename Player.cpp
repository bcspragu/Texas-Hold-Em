#include "Player.h"
#include <assert.h>

Player::Player(int startingAmount){
  wallet = startingAmount;
}

Move Player::getMove(Dealer* d){
  assert(false);
};

int Player::getAmountForMove(Dealer* d){
  assert(false);
};

Move Player::moveFromString(string moveStr){
  if ((moveStr == "Fold") || (moveStr == "FOLD") || (moveStr == "fold")){
    return FOLD;
  }else if((moveStr == "Call") || (moveStr == "CALL") || (moveStr == "call")){
    return CALL;
  }else if((moveStr == "Check") || (moveStr == "CHECK") || (moveStr == "check")){
    return CALL;
  }else if((moveStr == "Raise") || (moveStr == "RAISE") || (moveStr == "raise") || (moveStr == "Bet") || (moveStr == "BET") || (moveStr == "bet")){
    return RAISE;
  }else if((moveStr == "Allin") || (moveStr == "ALLIN") || (moveStr == "allin")){
    return ALLIN;
  }else{
    assert(false); // not a valid 
  }
}
