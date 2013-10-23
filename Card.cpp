#include "SuitValue.h"
#include "Card.h"

Card::Card(Suit s, Value v){
  suit = s;
  value = v;
}

Card::~Card(){}

Suit Card::suitFromInt(int i){
  Suit s;
  switch(i){
    case 0:
      s = SPADES;
      break;
    case 1:
      s = DIAMONDS;
      break;
    case 2:
      s = HEARTS;
      break;
    case 3:
      s = CLUBS;
      break;
  }
  return s;
}

Value Card::valueFromInt(int i){
  Value v;
  switch(i){
    case 0:
      v = ONE;
      break;
    case 1:
      v = TWO;
      break;
    case 2:
      v = THREE;
      break;
    case 3:
      v = FOUR;
      break;
    case 4:
      v = FIVE;
      break;
    case 5:
      v = SIX;
      break;
    case 6:
      v = SEVEN;
      break;
    case 7:
      v = EIGHT;
      break;
    case 8:
      v = NINE;
      break;
    case 9:
      v = TEN;
      break;
    case 10:
      v = JACK;
      break;
    case 11:
      v = QUEEN;
      break;
    case 12:
      v = KING;
      break;
    case 13:
      v = ACE;
      break;
  }
  return v;
}
