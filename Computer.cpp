#include <iostream>
#include <map>
#include <algorithm>
#include "Computer.h"
#include "Dealer.h"
//Needs to look at cards in hand and on table and decide whether to 
//bet, call, or fold. This senario will be different for the first
//round of betting, due to the fact that it is an incomplete hand
//(only 2 cards) and is highly subjective to chance

using std::cout;
using std::endl;

Computer::Computer(int startingAmount) : Player(startingAmount) {
  wallet = startingAmount;
  lastMove = "starting game";
}

int Computer::getDecision(int handValue){
  int random = (rand() % 100 + 1);

  if(handValue < 25){
    //this controls initial bet stage (just pocket cards)
    if(handValue >= 9){
      if(random > 50){
        return 1;
      }else{
        return 0;
      }
    }

    if((handValue >= 7) && (handValue < 9)){
      return 0;
    }

    if(handValue < 7){
      if(random > 55){
        return 0;
      }else if((random > 0) && (random < 5)){
        return 1;
      }else{
        return 2;
      }
    }
  }
  //these control bet stages 2 and on
  if(handValue > 50000){
    if(random > 50){
      return 4;
    }else{
      return 3;
    }
  }else if((handValue>30000) && (handValue <= 50000)){
    if(random > 50){
      return 3;
    }else if((random > 0) && (random < 10)){
      return 4;
    }else{
      return 5;
    }
  }else if((handValue <=3000) && (handValue >= 30)){
    if(random > 40){
      return 5;
    }else if(random < 30){
      return 3;
    }else{      
      return 4;
    }
  }
}

int Computer::getRaiseAmount(Dealer *d){ 

  int random = (rand() % 100 + 1);
  int pot = (*d).pot;
  int currentBet= (*d).betValue;
  int availableWallet = wallet - currentBet;

  //raiseing for a good pocket hand
  if((handValue >= 15) && (handValue <= 20)){

    if(random>=50){                                           // 50% chance of raising by 40% of the pot
      if(((4*pot)/10) <= availableWallet){
        return ((4*pot)/10);
      }else{
        return availableWallet;                               // if 40% of pot is more then available wallet, all-in
      }
    }else{
      if(((2*pot)/10) <= availableWallet){                    // 50% chance of raising by 20% of the pot
        return ((2*pot)/10);
      }else{
        return availableWallet;
      }
    }
  }else if (handValue < 15){

    if(((1*pot)/10) <= availableWallet){
      return ((1*pot)/10);
    }else{
      return availableWallet;
    }
  }else if (handValue > 80000){

    if(random >= 50){
      return availableWallet;
    }else if (((5*pot)/10) <= availableWallet){
      return ((5*pot)/10);
    }else{
      return availableWallet;
    }  
  }else if ((handValue <=80000) && (handValue >40000)){
    if (random >= 50){
      if(((3*pot)/10) <= availableWallet){
        return ((3*pot)/10);
      }else{
        return availableWallet;
      }
    }else if(random < 5){
      return availableWallet;
    }else{
      if((pot/10) <= availableWallet){
        return (pot/10);
      }else{
        return availableWallet;
      }
    }
  }else if((handValue <= 40000) && (handValue >25)){
    if(random >= 30){
      if(((2*pot)/10) <= availableWallet){
        return ((2*pot)/10);
      }else{
        return availableWallet;
      }
    }else if (random < 3){
      return availableWallet;
    }else{
      if ((pot/10) <= availableWallet){
        return (pot/10);
      }else {
        return availableWallet;
      }
    }

  }
  return ((availableWallet*2)/30);

}


//int Computer::getRaiseAmount(int handValue){
//return 0;
//}


/*Ace = 10 points
  King = 8 points
  Queen = 7 points
  Jack = 6 points
  10 through 2 = half of face value (i.e. 10 = 5, 9 = 4.5)
  Pairs, multiply score by 2 (i.e. KK = 16), minimum score for a pair is 5 (so pairs of 2 through 4 get a 5 score)
  Suited cards, add two points to highest card score
  Connectors add 1 point (i.e. KQ)
  One gap, subtract 1 point (i.e. T8)
  Two gap, subtract 2 points (i.e. AJ)
  Three gap, subtract 4 points (i.e. J7)
  Four or more gap, subtract 5 points (i.e. A4)
  */
