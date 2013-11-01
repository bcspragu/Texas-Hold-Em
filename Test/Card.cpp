#include <string>
#include "Card.h"

using std::string;

Card::Card(Suit s, Value v){
  suit = s;
  value = v;
}

Card::Card(string s){
  string su;
  string va;
  va += s[0];
  if(s[0] == '1'){
    va += s[1];
  }
  //Last character
  su = *s.rbegin();
  if(va == "2"){
    value = (Value)0;
  }else if(va == "3"){
    value = (Value)1;
  }else if(va == "4"){
    value = (Value)2;
  }else if(va == "5"){
    value = (Value)3;
  }else if(va == "6"){
    value = (Value)4;
  }else if(va == "7"){
    value = (Value)5;
  }else if(va == "8"){
    value = (Value)6;
  }else if(va == "9"){
    value = (Value)7;
  }else if(va == "10"){
    value = (Value)8;
  }else if(va == "J"){
    value = (Value)9;
  }else if(va == "Q"){
    value = (Value)10;
  }else if(va == "K"){
    value = (Value)11;
  }else if(va == "A"){
    value = (Value)12;
  } 
  if(su == "S"){
    suit = (Suit)0;
  }else if(su == "D"){
    suit = (Suit)1;
  }else if(su == "H"){
    suit = (Suit)2;
  }else if(su == "C"){
    suit = (Suit)3;
  }
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

//Take the original cardString, and shorten it. ex King of Hearts = KH
string Card::shortCardString(){
  string cardString = Card::cardString();
  string shortString;
  int spaceCount = 0;
  string::iterator itr;
  shortString += cardString[0];
  if(cardString[0] == '1'){
    shortString += cardString[1];
  }
  for(itr = cardString.begin(); itr < cardString.end(); itr++){
    if(spaceCount == 2){
      shortString += (*itr);
      break;
    }
    //Character is a space
    if((*itr) == ' '){
      spaceCount++;
    }
  }
  return shortString;
}

bool Card::operator<(const Card &other) const {
  return value < other.value;
}
