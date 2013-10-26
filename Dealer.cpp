#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "Deck.h"
#include "Dealer.h"
#include "Card.h"

using std::cout;
using std::endl;

void testCardChecking();
void testHand(std::vector<Card> hand);

int main(){
  Dealer d;
  testCardChecking();
}

Dealer::Dealer(){
  deck.shuffle();
  std::vector<Player>::iterator pitr;
  //Deal two cards to each player
  for(int i = 0; i < 2; i++){
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      (*pitr).hand.push_back(deck.dealCard());
    }
  }
}

Dealer::~Dealer(void){}

//A royal flush is just a straight flush from 10-ACE
bool Dealer::royalFlush(std::vector<Card> hand){
  return straightFlush(hand) && highestValue(hand) == ACE;
}

//A straight flush is just a straight and a flush
bool Dealer::straightFlush(std::vector<Card> hand){
  return straight(hand) && flush(hand);
}

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

Value Dealer::highestValue(std::vector<Card> hand){
  std::sort(hand.begin(),hand.end());
  return hand.back().value;
}

void testCardChecking(){
  std::vector<Card> royal;
  royal.push_back(Card("AH"));
  royal.push_back(Card("KH"));
  royal.push_back(Card("QH"));
  royal.push_back(Card("JH"));
  royal.push_back(Card("10H"));
  testHand(royal);

  std::vector<Card> straightf;
  straightf.push_back(Card("9H"));
  straightf.push_back(Card("KH"));
  straightf.push_back(Card("QH"));
  straightf.push_back(Card("JH"));
  straightf.push_back(Card("10H"));
  testHand(straightf);

  std::vector<Card> four;
  four.push_back(Card("9H"));
  four.push_back(Card("9C"));
  four.push_back(Card("9S"));
  four.push_back(Card("9D"));
  four.push_back(Card("10H"));
  testHand(four);

  std::vector<Card> full;
  full.push_back(Card("KH"));
  full.push_back(Card("KC"));
  full.push_back(Card("KD"));
  full.push_back(Card("JH"));
  full.push_back(Card("JS"));
  testHand(full);

  std::vector<Card> flush;
  flush.push_back(Card("8H"));
  flush.push_back(Card("2H"));
  flush.push_back(Card("7H"));
  flush.push_back(Card("4H"));
  flush.push_back(Card("AH"));
  testHand(flush);

  std::vector<Card> straight;
  straight.push_back(Card("5H"));
  straight.push_back(Card("6C"));
  straight.push_back(Card("8D"));
  straight.push_back(Card("7S"));
  straight.push_back(Card("4C"));
  testHand(straight);

  std::vector<Card> three;
  three.push_back(Card("8H"));
  three.push_back(Card("8C"));
  three.push_back(Card("8D"));
  three.push_back(Card("2H"));
  three.push_back(Card("5S"));
  testHand(three);

  std::vector<Card> two;
  two.push_back(Card("3H"));
  two.push_back(Card("3C"));
  two.push_back(Card("4D"));
  two.push_back(Card("2H"));
  two.push_back(Card("2S"));
  testHand(two);

  std::vector<Card> pair;
  pair.push_back(Card("3H"));
  pair.push_back(Card("3C"));
  pair.push_back(Card("4D"));
  pair.push_back(Card("7H"));
  pair.push_back(Card("AS"));
  testHand(pair);

  std::vector<Card> high;
  high.push_back(Card("7H"));
  high.push_back(Card("3C"));
  high.push_back(Card("2D"));
  high.push_back(Card("9H"));
  high.push_back(Card("JS"));
  testHand(high);
}

void testHand(std::vector<Card> hand){
  string handString = "Cards in hand: ";
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    handString += (*itr).shortCardString() + " ";
  }
  cout << handString << endl << "Hand is ";
  if(Dealer::royalFlush(hand)){
    cout << "a Royal Flush" << endl;
    return;
  }
  if(Dealer::straightFlush(hand)){
    cout << "a Straight Flush" << endl;
    return;
  }
  if(Dealer::fourOfAKind(hand)){
    cout << "Four of a Kind" << endl;
    return;
  }
  if(Dealer::fullHouse(hand)){
    cout << "a Full House" << endl;
    return;
  }
  if(Dealer::flush(hand)){
    cout << "a Flush" << endl;
    return;
  }
  if(Dealer::straight(hand)){
    cout << "a Straight" << endl;
    return;
  }
  if(Dealer::threeOfAKind(hand)){
    cout << "Three of a Kind" << endl;
    return;
  }
  if(Dealer::twoPair(hand)){
    cout << "Two Pair" << endl;
    return;
  }
  if(Dealer::pair(hand)){
    cout << "a Pair" << endl;
    return;
  }
  cout << "High card value: " << Dealer::highestValue(hand) << endl;
}
