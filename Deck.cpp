#include <algorithm>
#include <time.h>
#include "Deck.h"
#include "Card.h"
#include "SuitValue.h"

Deck::Deck(){
  fill();
}

Deck::~Deck(){}

void Deck::fill(){
  cards.clear();
  for(int i = 0; i < 52; i++){
    Suit s = Card::suitFromInt(i/13);
    Value v = Card::valueFromInt(i % 13);
    cards.push_back(Card(s,v));
  }

}

void Deck::shuffle(){
  std::srand(time(0));
  std::random_shuffle(cards.begin(),cards.end());
}

Card Deck::dealCard(){
  Card top = cards.front();
  cards.erase(cards.begin());
  return top;
}

int Deck::cardCount(){
  return cards.size();
}

string Deck::displayHand(std::vector<Card> cards){
  string handString = "";
  std::vector<Card>::iterator itr;
  for(itr = cards.begin(); itr != cards.end(); ++itr){
    handString += (*itr).shortCardString() + " ";
  }
  return handString;
}
