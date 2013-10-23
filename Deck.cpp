#include <algorithm>
#include "Deck.h"

using namespace std;

Deck::Deck(){
  for(int i = 0; i < 52; i++){
    cards.push_back(Card((Suit)i/4,(Value)i%14));
  }
}

void Deck::shuffle(){
  random_shuffle(cards.begin(),cards.end());
}

