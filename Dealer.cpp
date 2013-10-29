#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "Deck.h"
#include "Dealer.h"
#include "Card.h"
#include "Player.h"
#include "User.h"
#include "Computer.h"

using std::cout;
using std::cin;
using std::endl;

void testHands();
void testHand(std::vector<Card> hand);

int main(){
  Dealer d;
  testHands();
  std::vector<Card> pocket;
  pocket.push_back(Card("7H"));
  pocket.push_back(Card("3C"));
  
  cout<< "Your pocket rate is: " << Computer::ratePocketCards(pocket) << endl;
  

}

Dealer::Dealer(){
  deck.shuffle();
  for(int i = 0; i < 5; i++){
    computers.push_back(Computer(500));
  }
  User user = User(500);
  std::vector<Computer>::iterator pitr;
  //Deal two cards to each player
  for(int i = 0; i < 2; i++){
    user.hand.push_back(deck.dealCard());
    for(pitr = computers.begin(); pitr != computers.end(); ++pitr){
      (*pitr).hand.push_back(deck.dealCard());
    }
  }

  while(userStillAlive()){
    //Show everyone their cards, take everyones input
    string choice;
    cout << "Your cards: " << Deck::displayHand(user.hand) << endl;
    cout << "Your choice: ";
    cin >> choice;
    if(choice == "bet"){
      int amount;
      cout << "How much: ";
      cin >> amount;
      if(amount < user.wallet){
        user.wallet -= amount;
        pot += amount;
      }else{
        cout << "You don't have that much money" << endl;
      }
   
    }    

    //Deal three cards
    //Take everyone's input
    //Deal a card
    //Take everyone's input
    //Deal a card
    //Take everyone's input
    
  }
}

Dealer::~Dealer(void){}

bool Dealer::userStillAlive(){
  //First player is user, smallBlind*2 is large blind
  return computers.front().wallet > smallBlind*2;
}
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

  int numPairs = 0;
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

void testHands(){
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
  cout << Deck::displayHand(hand) << endl;
  cout << "Hand is ";
  if(Dealer::royalFlush(hand)){
    cout << "a Royal Flush" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::straightFlush(hand)){
    cout << "a Straight Flush" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::fourOfAKind(hand)){
    cout << "Four of a Kind" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::fullHouse(hand)){
    cout << "a Full House" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::flush(hand)){
    cout << "a Flush" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::straight(hand)){
    cout << "a Straight" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::threeOfAKind(hand)){
    cout << "Three of a Kind" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::twoPair(hand)){
    cout << "Two Pair" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  if(Dealer::pair(hand)){
    cout << "a Pair" << endl;
    cout << "Score: " << Dealer::scoreHand(hand) << endl;
    return;
  }
  cout << "High card value: " << Dealer::highestValue(hand) << endl;
  cout << "Score: " << Dealer::scoreHand(hand) << endl;
}
