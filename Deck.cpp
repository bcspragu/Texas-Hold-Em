#include <algorithm>
#include "Deck.h"
#include "Card.h"
#include "SuitValue.h"

Deck::Deck(){
  for(int i = 0; i < 52; i++){
    Suit s = Card::suitFromInt(i/13);
    Value v = Card::valueFromInt(i % 13);
    cards.push_back(Card(s,v));
  }
}

Deck::~Deck(){}

void Deck::shuffle(){
  std::random_shuffle(cards.begin(),cards.end());
}

