#include <string>
#include "SuitValue.h"
#include "Card.h"

using std::string;

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
      v = TWO;
      break;
    case 1:
      v = THREE;
      break;
    case 2:
      v = FOUR;
      break;
    case 3:
      v = FIVE;
      break;
    case 4:
      v = SIX;
      break;
    case 5:
      v = SEVEN;
      break;
    case 6:
      v = EIGHT;
      break;
    case 7:
      v = NINE;
      break;
    case 8:
      v = TEN;
      break;
    case 9:
      v = JACK;
      break;
    case 10:
      v = QUEEN;
      break;
    case 11:
      v = KING;
      break;
    case 12:
      v = ACE;
      break;
  }
  return v;
}

string Card::cardString(){
  string suitString;
  switch(suit){
    case HEARTS:
      suitString = "Hearts";
      break;
    case DIAMONDS:
      suitString = "Diamonds";
      break;
    case SPADES:
      suitString = "Spades";
      break;
    case CLUBS:
      suitString = "Clubs";
      break;
  }

  string valString;
  switch(value){
    case TWO:
      valString = "2 of";
      break;
    case THREE:
      valString = "3 of";
      break;
    case FOUR:
      valString = "4 of";
      break;
    case FIVE:
      valString = "5 of";
      break;
    case SIX:
      valString = "6 of";
      break;
    case SEVEN:
      valString = "7 of";
      break;
    case EIGHT:
      valString = "8 of";
      break;
    case NINE:
      valString = "9 of";
      break;
    case TEN:
      valString = "10 of";
      break;
    case JACK:
      valString = "Jack of";
      break;
    case QUEEN:
      valString = "Queen of";
      break;
    case KING:
      valString = "King of";
      break;
    case ACE:
      valString = "Ace of";
      break;
  }
  return valString+" "+suitString;
}
