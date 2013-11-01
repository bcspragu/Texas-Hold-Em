#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include <cstring>
#include <assert.h>
#include <sstream>
#include "Dealer.h"
#include "Player.h"
#include "User.h"
#include "Computer.h"
#include "Move.h"

using std::cout;
using std::cin;
using std::endl;

std::stringstream messageString;

int keynew = 0;
int bet = 0;

char key;
char key2;
int cardX = 0;
int cardY = 0;

void setText(string target, string text);

void setText(string target, string text){
  int xpos,ypos;
  if(target == "B11"){ //Box 1,1 top left
    ypos = 30;
    xpos = 55;
  }else if(target == "B12"){ //Box 1,2 bottom left
    ypos = 37;
    xpos = 55;
  }else if(target == "B21"){ //Box 2,1 top center
    ypos = 30;
    xpos = 75;
  }else if(target == "B22"){ //Box 1,2 bottom center
    ypos = 37;
    xpos = 75;
  }else if(target == "B31"){ //Box 3,1 top right
    ypos = 30;
    xpos = 94;
  }else if(target == "B32"){ //Box 3,2 bottom right
    ypos = 37;
    xpos = 94;
  }else if(target == "P1T"){ //Player 1 top box
    ypos = 34;
    xpos = 36;
  }else if(target == "P1B"){ //Player 1 bottom box
    ypos = 36;
    xpos = 36;
  }else if(target == "P2T"){ //Player 3 top box
    ypos = 24;
    xpos = 11;
  }else if(target == "P2B"){ //Player 3 bottom box
    ypos = 26;
    xpos = 11;
  }else if(target == "P3T"){ //Player 4 top box
    ypos = 12;
    xpos = 11;
  }else if(target == "P3B"){ //Player 4 bottom box
    ypos = 14;
    xpos = 11;
  }else if(target == "P4T"){ //Player 2 top box
    ypos = 7;
    xpos = 48;
  }else if(target == "P4B"){ //Player 2 bottom box
    ypos = 9;
    xpos = 48;
  }else if(target == "P5T"){ //Player 6 top box
    ypos = 12;
    xpos = 79;
  }else if(target == "P5B"){ //Player 6 bottom box
    ypos = 14;
    xpos = 79;
  }else if(target == "P6T"){ //Player 5 top box
    ypos = 24;
    xpos = 79;
  }else if(target == "P6B"){ //Player 5 bottom box
    ypos = 26;
    xpos = 79;
  }else if(target == "C"){ //Community header
    ypos = 15;
    xpos = 51;
  }
}

void Dealer::showAllCards(){
  std::vector<Player*>::iterator pitr;
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    int suit1 = (**pitr).hand.front().suit+1;
    int value1 = (**pitr).hand.front().value+2;
    int suit2 = (**pitr).hand.back().suit+1;
    int value2 = (**pitr).hand.back().value+2;
    int ypos,xpos;
    switch((**pitr).ID){
      case 1:
        xpos = 35;
        ypos = 29;
        break;
      case 2:
        xpos = 10;
        ypos = 19;
        break;
      case 3:
        xpos = 10;
        ypos = 7;
        break;
      case 4:
        xpos = 47;
        ypos = 2;
        break;
      case 5:
        xpos = 78;
        ypos = 7;
        break;
      case 6:
        xpos = 78;
        ypos = 19;
        break;
    }
  }

  setText("B12","New Hand?");
  setText("C","");
  bool onGoing = true;
  while(onGoing){
    keynew = key - 48;
    // if a mouse event occurred
    if (key == -1) {
      // record the location of the mouse event
      if((cardX >= 50) && (cardX <= 68) && (cardY >= 35) && (cardY <= 40)){
        setText("B12","Playing");
        messageString.str("");
        messageString << "Playing";
        onGoing = false;
      }else if((cardX >= 87) && (cardX <= 105) && (cardY >= 35) && (cardY <= 40)){
        exit(0);
      }
    }
  }
}
Dealer::Dealer(){
  pot = 0;
  numPlayers = 6;
  User* user = new User(500);
  user->ID = 1;
  players.push_back(user);
  for(int i = 1; i < numPlayers; i++){
    players.push_back(new Computer(500));
    players.back()->ID = i+1;
  }

  std::vector<Player*>::iterator pitr;

  smallBlindLoc = -1;
  //Game loop

  while((*players.front()).wallet > largeBlind){

    //Fill and shuffle the deck before each hand
    deck.fill();
    deck.shuffle();

    //Clear out the community cards
    community.clear();

    //Kill all the players that can't make large blind
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      if((**pitr).wallet < largeBlind){
        //cout << "Player " << (**pitr).ID << " has ran out of money" << endl;
        (*pitr) = NULL; //GET NULLIFIED
        numPlayers--;
      }
    }

    if(numPlayers == 1){
      //Game Over, you win
      return;
    }

    dealHands();
    //Resetting things between rounds

    pot = 0;

    do{
      smallBlindLoc = (smallBlindLoc+1) % players.size();
    }
    while(players[smallBlindLoc] == NULL);

    //Try the next player first
    largeBlindLoc = (smallBlindLoc+1) % players.size();
    while(players[largeBlindLoc] == NULL){
      largeBlindLoc = (largeBlindLoc+1) % players.size();
    }

    currentRound = players;
    players[smallBlindLoc]->wallet -= smallBlind;
    players[largeBlindLoc]->wallet -= largeBlind;
    pot += smallBlind+largeBlind;

    roundOfBetting(2);
    dealFlop();
    roundOfBetting(0);
    dealTurn();
    roundOfBetting(0);
    dealRiver();
    roundOfBetting(0);

    std::vector<Player*> winners = determineWinner();
    std::stringstream win_strm;
    showAllCards();
  }
  if((*players.front()).wallet < largeBlind){
    //cout << "User has lost the game." << endl;
  }
}
void Dealer::roundOfBetting(int handOffset){
  if(playersStillIn(currentRound) == 1){
    return; //There's only one person, we don't need to play
  }
  //Reset the value to stay in to the large blind
  betValue = largeBlind;
  
  //All set if nobody has raised, means everyone has folded or checked
  bool allSet = false;
  
  //Start by setting everyone's contribution to the current round of betting to zero
  std::vector<Player*>::iterator pitr;
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    if((*pitr) != NULL){
      (**pitr).currentContribution = 0;
      (**pitr).allIn = false;
    }
  }
  while(!allSet){
    //cot << "Pot: $" << pot << " Bet: $" << betValue << endl;
    allSet = true;
    for(int i = 0; i < currentRound.size(); i++){
      int index = (smallBlindLoc+handOffset+i) % currentRound.size();
      if(currentRound[index] != NULL){
        Player* player = currentRound[index];
        if(!(player->allIn)){
          Move move = player->getMove(this);
          if(move == RAISE){
            //The amount they spend is the amount they need to add to match the current bet, plus their raise
            int raise = player->getAmountForMove(this);
            int amount = (betValue - player->currentContribution) + raise;
            if(amount <= player->wallet){ //If they have enough money to do this
              betValue += raise;
              player->currentContribution += amount;
              player->wallet -= amount;
              pot += amount;
            }else{ //If they don't have enough, put them all in
              player->allIn = true;
              //Only increase the actual bet by how much new they're adding in
              betValue += player->wallet - (betValue - player->currentContribution);
              player->currentContribution += player->wallet;
              pot += player-> wallet;
              player->wallet = 0;
            }
            allSet = false;
          }else if(move == CALL){
            int amount = betValue - player->currentContribution;
            if(amount <= player->wallet){
              player->currentContribution += amount;
              player->wallet -= amount;
              pot += amount;
            }else{ //If they don't have enough, put them all in
              player->allIn = true;
              //Only increase the actual bet by how much new they're adding in
              betValue += player->wallet - (betValue - player->currentContribution);
              player->currentContribution += player->wallet;
              pot += player-> wallet;
              player->wallet = 0;
              allSet = false;
            }
          }else if(move == FOLD){
            currentRound[index] = NULL;
            if(playersStillIn(currentRound) == 1){
              return; //There's only one person, we don't need to play
            }
          }else if(move == ALLIN){
            //Only increase the actual bet by how much new they're adding in
            betValue += player->wallet - (betValue - player->currentContribution);
            player->currentContribution += player->wallet;
            pot += player-> wallet;
            player->wallet = 0;
            allSet = false;
            player->allIn = true;
          }else{
            assert(false);
          }
          player->updateWallet();
        }
      }
    }
  }
  updateBet();
}

void Dealer::updateBet(){
  char betstr[21];
  sprintf(betstr, "Bet: $%d", betValue);
}

void Dealer::dealHands(){
  std::vector<Player*>::iterator pitr;
  //Clear out each user's hand, then deal them a new one
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    if((*pitr) != NULL){
      (**pitr).hand.clear();
    }
  }
  for(int i = 0; i < 2; i++){
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      if((*pitr) != NULL){
        (**pitr).hand.push_back(deck.dealCard());
      }
    }
  }
  Card card1 = players.front()->hand.front();
  Card card2 = players.front()->hand.back();
}

void Dealer::updateValuesOnScreen(){
  char tmpstr[21];
  updateBet();
}

void Dealer::dealRiver(){
  community.push_back(deck.dealCard());
  setText("C","River");

}

void Dealer::dealTurn(){
  community.push_back(deck.dealCard());
  setText("C","Turn");
}

void Dealer::dealFlop(){
  for(int i = 0; i < 3; i++){
    community.push_back(deck.dealCard());
  }
  setText("C","Flop");
}
//A royal flush is just a straight flush from 10-ACE
bool Dealer::royalFlush(std::vector<Card> hand){
  return straightFlush(hand) && highestValue(hand) == ACE;
}

//A straight flush is just a straight and a flush
bool Dealer::straightFlush(std::vector<Card> hand){
  return straight(hand) && flush(hand); }

  bool Dealer::fourOfAKind(std::vector<Card> hand){
    //Map from Card value to the number of those cards you have
    std::map<Value, int> cardCounts;

    //Iterate over cards and initialize the map to zero at those values
    std::vector<Card>::iterator itr;
    for(itr = hand.begin(); itr != hand.end(); ++itr){
      cardCounts[(*itr).value] = 0;
    }

    //Iterate over the cards again and increment the count at that value
    for(itr = hand.begin(); itr != hand.end(); ++itr){
      cardCounts[(*itr).value]++;
    }

    //Iterate through the map and look for a count of 4
    std::map<Value,int>::iterator mitr;
    for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
      if((*mitr).second == 4){
        return true;
      }
    }
    return false;
  }

Value Dealer::valueOfFourOfAKind(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 4){
      return (*mitr).first;
    }
  }
  //Should never reach this, method only called once 4 of a kind exists
  return TWO;
}

bool Dealer::fullHouse(std::vector<Card> hand){
  return threeOfAKind(hand) && pair(hand);
}

bool Dealer::flush(std::vector<Card> hand){
  Suit target = hand.front().suit;

  //Iterate over cards and see if they all have the same sui
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    if((*itr).suit != target){
      return false;
    }
  }
  return true;
}

bool Dealer::straight(std::vector<Card> hand){
  std::sort(hand.begin(),hand.end());
  Value lowest = hand.front().value;
  Value previous = lowest;
  //Iterate starting with the second card
  std::vector<Card>::iterator itr;
  for(itr = hand.begin()+1; itr != hand.end(); ++itr){
    //Those final conditions handle ACE as a low value
    if(((*itr).value - previous) != 1 && !(previous == FIVE && (*itr).value == ACE)){
      return false;
    }else {
      previous = (*itr).value;
    }
  }
  return true;
}

bool Dealer::threeOfAKind(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 3){
      return true;
    }
  }
  return false;
}

Value Dealer::valueOfThreeOfAKind(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 3){
      return (*mitr).first;
    }
  }
  //Should never reach this, method only called once 3 of a kind exists
  return TWO;
}

bool Dealer::twoPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  int numPairs = 0;
  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2){
      numPairs++;
    }
  }
  return numPairs == 2;
}

Value Dealer::higherPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  int numPairs = 0;
  Value highestValue = TWO;
  //Iterate through the map and look for a count of 2
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2 && (*mitr).first > highestValue){
      highestValue = (*mitr).first;
    }
  }
  return highestValue;
}

Value Dealer::lowerPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  Value lowestValue = ACE;
  //Iterate through the map and look for a count of 2
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2 && (*mitr).first < lowestValue){
      lowestValue = (*mitr).first;
    }
  }
  return lowestValue;
}

bool Dealer::pair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  int numPairs = 0;
  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2){
      numPairs++;
    }
  }
  return numPairs == 1;
}

Value Dealer::valueOfPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 2
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2){
      return (*mitr).first;
    }
  }
  //Should never reach this, method only called once 3 of a kind exists
  return TWO;
}

Value Dealer::highestValue(std::vector<Card> hand){
  std::sort(hand.begin(),hand.end());
  return hand.back().value;
}

int Dealer::scoreHand(std::vector<Card> hand){
  int primary = 0;
  int secondary = 0;
  int tertiary = 0;
  if(Dealer::royalFlush(hand)){
    primary = 9;
    secondary = 0;
    tertiary = 0;
  }
  else if(Dealer::straightFlush(hand)){
    primary = 8;
    secondary = highestValue(hand);
    tertiary = 0;
  }
  else if(Dealer::fourOfAKind(hand)){
    primary = 7;
    secondary = valueOfFourOfAKind(hand);
    tertiary = 0;  //Impossible in texas hold'em
  }
  else if(Dealer::fullHouse(hand)){
    primary = 6;
    secondary = valueOfThreeOfAKind(hand);
    tertiary = valueOfPair(hand);
  }
  else if(Dealer::flush(hand)){
    primary = 5;
    secondary = highestValue(hand);
    tertiary = 0; //Tie
  }
  else if(Dealer::straight(hand)){
    primary = 4;
    secondary = highestValue(hand);
    tertiary = 0; //Tie
  }
  else if(Dealer::threeOfAKind(hand)){
    primary = 3;
    secondary = valueOfThreeOfAKind(hand);
    tertiary = highestValue(hand);
  }
  else if(Dealer::twoPair(hand)){
    primary = 2;
    secondary = higherPair(hand);
    tertiary = lowerPair(hand);
  }
  else if(Dealer::pair(hand)){
    primary = 1;
    secondary = valueOfPair(hand);
    tertiary = highestValue(hand);
  }
  else{//High card
    primary = 0;
    secondary = highestValue(hand);
    tertiary = 0;
  }
  //Unique hand score, weighted by characteristic importance
  return primary*10000+secondary*100+tertiary;
}

int Dealer::scoreBestHand(std::vector<Card> hand){
  std::vector<Card> moreThanFiveCardHand;
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), hand.begin(), hand.end());
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), community.begin(), community.end());
  int index1 = 0;
  int index2 = 0;
  int highestScore = 0;
  if(moreThanFiveCardHand.size() == 7){
    for(int i = 0; i < 21; i++){
      int score = scoreHand(fiveCardHand(moreThanFiveCardHand,index1,index2));
      if(score > highestScore){
        highestScore = score;
      }
      if(index2 == 6){
        index1++;
        index2 = index1+1;
      }else{
        index2++;
      }
    }
  }else{  //Six card hand
    for(int i = 0; i < 6; i++){
      int score = scoreHand(fiveCardHand(moreThanFiveCardHand,i,-1));
      if(score > highestScore){
        highestScore = score;
      }
    }
  }
  return highestScore;
}

std::vector<Card> Dealer::bestHand(std::vector<Card> hand){
  std::vector<Card> moreThanFiveCardHand;
  std::vector<Card> highestHand;
  std::vector<Card> tempHand;
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), hand.begin(), hand.end());
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), community.begin(), community.end());
  int index1 = 0;
  int index2 = 0;
  int highestScore = 0;
  if(moreThanFiveCardHand.size() == 7){
    for(int i = 0; i < 21; i++){
      tempHand = fiveCardHand(moreThanFiveCardHand,index1,index2);
      int score = scoreHand(tempHand);
      if(score > highestScore){
        highestScore = score;
        highestHand = tempHand;
      }
      if(index2 == 6){
        index1++;
        index2 = index1+1;
      }else{
        index2++;
      }
    }
  }else{  //Six card hand
    for(int i = 0; i < 6; i++){
      tempHand = fiveCardHand(moreThanFiveCardHand,i,-1);
      int score = scoreHand(tempHand);
      if(score > highestScore){
        highestScore = score;
        highestHand = tempHand;
      }
    }
  }
  return highestHand;
}


std::vector<Player*> Dealer::determineWinner(){
  std::vector<Player*> winners;
  std::vector<Player*>::iterator itr;
  int highestScore = 0;
  //Find the highest score
  for(itr = currentRound.begin(); itr != currentRound.end(); ++itr){
    if((*itr) != NULL){
      int score = scoreBestHand((**itr).hand);
      if(score >= highestScore){
        highestScore = score;
      }
    }
  }

  //Add all players with those hands to winners array
  for(itr = currentRound.begin(); itr != currentRound.end(); ++itr){
    if((*itr) != NULL){
      if(scoreBestHand((**itr).hand) == highestScore){
        winners.push_back(*itr);
      }
    }
  }
  return winners;
}

std::vector<Card> Dealer::fiveCardHand(std::vector<Card> largeHand, int i1, int i2){
  std::vector<Card> newHand;
  int length = largeHand.size();
  for(int i = 0; i < length; i++){
    if(i != i1 && i != i2){
      newHand.push_back(largeHand[i]);
    }
  }
  return newHand;
}

int Dealer::playersStillIn(std::vector<Player*> current){
  int count = 0;
  std::vector<Player*>::iterator itr;
  for(itr = current.begin(); itr != current.end(); ++itr){
    if(*itr != NULL){
      count++;
    }
  }
  return count;
}
