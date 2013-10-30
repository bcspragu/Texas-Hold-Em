#include "Card.h"
#include "Dealer.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

void testHands();
void testHand(std::vector<Card> hand);
int main(){
  testHands();
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
