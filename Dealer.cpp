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

  cout << "Royal: " << Dealer::royalFlush(royal) << endl;
  cout << "Straight Flush: " << Dealer::straightFlush(royal) << endl;
  cout << "Four of a Kind: " << Dealer::fourOfAKind(royal) << endl;
  cout << "Full House: " << Dealer::fullHouse(royal) << endl;
  cout << "Flush: " << Dealer::flush(royal) << endl;
  cout << "Straight: " << Dealer::straight(royal) << endl;
  cout << "Three of a Kind: " << Dealer::threeOfAKind(royal) << endl;
  cout << "Two Pair:" << Dealer::twoPair(royal) << endl;
  cout << "Pair: " << Dealer::pair(royal) << endl;
  cout << "Highest Value: " << Dealer::highestValue(royal) << endl;

  std::vector<Card> full;
  full.push_back(Card("KH"));
  full.push_back(Card("KC"));
  full.push_back(Card("KD"));
  full.push_back(Card("JH"));
  full.push_back(Card("JS"));

  cout << "Royal: " << Dealer::royalFlush(full) << endl;
  cout << "Straight Flush: " << Dealer::straightFlush(full) << endl;
  cout << "Four of a Kind: " << Dealer::fourOfAKind(full) << endl;
  cout << "Full House: " << Dealer::fullHouse(full) << endl;
  cout << "Flush: " << Dealer::flush(full) << endl;
  cout << "Straight: " << Dealer::straight(full) << endl;
  cout << "Three of a Kind: " << Dealer::threeOfAKind(full) << endl;
  cout << "Two Pair:" << Dealer::twoPair(full) << endl;
  cout << "Pair: " << Dealer::pair(full) << endl;
  cout << "Highest Value: " << Dealer::highestValue(full) << endl;

  std::vector<Card> two;
  two.push_back(Card("3H"));
  two.push_back(Card("3C"));
  two.push_back(Card("4D"));
  two.push_back(Card("2H"));
  two.push_back(Card("2S"));

  cout << "Royal: " << Dealer::royalFlush(two) << endl;
  cout << "Straight Flush: " << Dealer::straightFlush(two) << endl;
  cout << "Four of a Kind: " << Dealer::fourOfAKind(two) << endl;
  cout << "two House: " << Dealer::fullHouse(two) << endl;
  cout << "Flush: " << Dealer::flush(two) << endl;
  cout << "Straight: " << Dealer::straight(two) << endl;
  cout << "Three of a Kind: " << Dealer::threeOfAKind(two) << endl;
  cout << "Two Pair:" << Dealer::twoPair(two) << endl;
  cout << "Pair: " << Dealer::pair(two) << endl;
  cout << "Highest Value: " << Dealer::highestValue(two) << endl;
}
