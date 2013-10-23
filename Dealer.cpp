#include <iostream>
#include <vector>
#include "Deck.h"
#include "Dealer.h"
#include "Card.h"

using namespace std;

Dealer::Dealer(){
  deck.shuffle();
}

Dealer::~Dealer(void){}

int main(){
  Dealer d;
  vector<Card>::iterator itr;
  vector<Card> cards = d.deck.cards;
  for(itr = cards.begin(); itr != cards.end(); ++itr){
    cout << (*itr).cardString() << endl;
  }
}
