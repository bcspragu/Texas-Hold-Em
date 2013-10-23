#include <iostream>
#include "Deck.h"
#include "Dealer.h"

using namespace std;

Dealer::Dealer(){
  deck.shuffle();
}

Dealer::~Dealer(void){}

int main(){
  cout << "Test" << endl;
}
