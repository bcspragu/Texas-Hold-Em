#include "Card.h"
#include "Dealer.h"
#include "User.h"
#include "Computer.h"
#include "Deck.h"
#include <vector>
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

void testHands();
string testHand(std::vector<Card> hand);
void testMoneys();
void testMoney(std::vector<Player*> players);
void testDecks();
void testDeck(Deck deck);

void assert_true(string one, string two);
void assert_true(int one, int two);
void assert_true(long one, long two);
void assert_true(double one, double two);
void assert_true(float one, float two);

int main(){
  testHands();
  testMoneys();
  testDecks();
}

void testHands(){
  std::vector<Card> royal;
  royal.push_back(Card("AH"));
  royal.push_back(Card("KH"));
  royal.push_back(Card("QH"));
  royal.push_back(Card("JH"));
  royal.push_back(Card("10H"));
  assert_true(testHand(royal),"Royal Flush");

  std::vector<Card> straightf;
  straightf.push_back(Card("9H"));
  straightf.push_back(Card("KH"));
  straightf.push_back(Card("QH"));
  straightf.push_back(Card("JH"));
  straightf.push_back(Card("10H"));
  assert_true(testHand(straightf),"Straight Flush");

  std::vector<Card> four;
  four.push_back(Card("9H"));
  four.push_back(Card("9C"));
  four.push_back(Card("9S"));
  four.push_back(Card("9D"));
  four.push_back(Card("10H"));
  assert_true(testHand(four),"Four of a Kind");

  std::vector<Card> full;
  full.push_back(Card("KH"));
  full.push_back(Card("KC"));
  full.push_back(Card("KD"));
  full.push_back(Card("JH"));
  full.push_back(Card("JS"));
  assert_true(testHand(full),"Full House");

  std::vector<Card> flush;
  flush.push_back(Card("8H"));
  flush.push_back(Card("2H"));
  flush.push_back(Card("7H"));
  flush.push_back(Card("4H"));
  flush.push_back(Card("AH"));
  assert_true(testHand(flush),"Flush");

  std::vector<Card> straight;
  straight.push_back(Card("5H"));
  straight.push_back(Card("6C"));
  straight.push_back(Card("8D"));
  straight.push_back(Card("7S"));
  straight.push_back(Card("4C"));
  assert_true(testHand(straight),"Straight");

  std::vector<Card> three;
  three.push_back(Card("8H"));
  three.push_back(Card("8C"));
  three.push_back(Card("8D"));
  three.push_back(Card("2H"));
  three.push_back(Card("5S"));
  assert_true(testHand(three),"Three of a Kind");

  std::vector<Card> two;
  two.push_back(Card("3H"));
  two.push_back(Card("3C"));
  two.push_back(Card("4D"));
  two.push_back(Card("2H"));
  two.push_back(Card("2S"));
  assert_true(testHand(two),"Two Pair");

  std::vector<Card> pair;
  pair.push_back(Card("3H"));
  pair.push_back(Card("3C"));
  pair.push_back(Card("4D"));
  pair.push_back(Card("7H"));
  pair.push_back(Card("AS"));
  assert_true(testHand(pair),"Pair");

  std::vector<Card> high;
  high.push_back(Card("7H"));
  high.push_back(Card("3C"));
  high.push_back(Card("2D"));
  high.push_back(Card("9H"));
  high.push_back(Card("JS"));
  assert_true(testHand(high),"High Card");
}

string testHand(std::vector<Card> hand){
  if(Dealer::royalFlush(hand)){
    return "Royal Flush";
  }
  if(Dealer::straightFlush(hand)){
    return "Straight Flush";
  }
  if(Dealer::fourOfAKind(hand)){
    return "Four of a Kind";
  }
  if(Dealer::fullHouse(hand)){
    return "Full House";
  }
  if(Dealer::flush(hand)){
    return "Flush";
  }
  if(Dealer::straight(hand)){
    return "Straight";
  }
  if(Dealer::threeOfAKind(hand)){
    return "Three of a Kind";
  }
  if(Dealer::twoPair(hand)){
    return "Two Pair";
  }
  if(Dealer::pair(hand)){
    return "Pair";
  }
  return "High Card";
}


void testMoneys(){
  std::vector<Player*> players;
  int numPlayers = 6;
  User* user = new User(500);
  user->ID = 1;
  players.push_back(user);
  for(int i = 1; i < numPlayers; i++){
    players.push_back(new Computer(500));
    players.back()->ID = i+1;
  }
  testMoney(players);
}

void testMoney(std::vector<Player*> players){
  std::vector<Player*>::iterator pitr;
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    assert_true((*pitr)->wallet,500);
  }
}

void testDecks(){
  Deck deck;
  deck.fill();
  testDeck(deck);
}

void testDeck(Deck deck){
  std::vector<int> letter;
  std::vector<int> numbers;

  for(int x = 0; x < 4; ++x)
      letter.push_back(0);
    for(int y = 0; y < 13; ++y)
      numbers.push_back(0);
  
    std::vector<Card>::iterator pitr;
  for(pitr = deck.cards.begin(); pitr != deck.cards.end(); ++pitr){
    letter[(*pitr).suit]++;
    numbers[(*pitr).value]++;
  }

  for(int a = 0; a < 4; ++a){
      assert_true(letter[a],13);
    }
    for(int b = 0; b < 13; ++b){
      assert_true(numbers[b],4);
    }
}

void assert_true(string one, string two){
  assert(one == two);
  cout << "Passed: " << one << " == " << two << endl;
}
void assert_true(int one, int two){
  assert(one == two);
  cout << "Passed: " << one << " == " << two << endl;
}
void assert_true(long one, long two){
  assert(one == two);
  cout << "Passed: " << one << " == " << two << endl;
}
void assert_true(double one, double two){
  assert(one == two);
  cout << "Passed: " << one << " == " << two << endl;
}
void assert_true(float one, float two){
  assert(one == two);
  cout << "Passed: " << one << " == " << two << endl;
}
