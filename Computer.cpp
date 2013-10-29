#include <iostream>
#include <map>
#include <algorithm>
#include "Computer.h"
//Needs to look at cards in hand and on table and decide whether to 
//bet, call, or fold. This senario will be different for the first
//round of betting, due to the fact that it is an incomplete hand
//(only 2 cards) and is highly subjective to chance

using std::cout;
using std::endl;

Computer::Computer(int startingAmount){
   wallet = startingAmount;
 }

  int Computer::ratePocketCards(std::vector<Card> hand){
  int great=0;
  int good=0;
  int ok=0;
  int questionable=0;
  int bad=0;
  int horrible=0;
  int counter=0;
  
  double handValue;

/*Ace = 10 points
King = 8 points
Queen = 7 points
Jack = 6 points
10 through 2 = half of face value (i.e. 10 = 5, 9 = 4.5)
Pairs, multiply score by 2 (i.e. KK = 16), minimum score for a pair is 5 (so pairs of 2 through 4 get a 5 score)
Suited cards, add two points to highest card score
Connectors add 1 point (i.e. KQ)
One gap, subtract 1 point (i.e. T8)
Two gap, subtract 2 points (i.e. AJ)
Three gap, subtract 4 points (i.e. J7)
Four or more gap, subtract 5 points (i.e. A4)
*/
std::sort(hand.begin(),hand.end());

  Card lowCard = hand.front();
  Card highCard = hand.back();
  
  std::map<Value, double> cardPoints; 

  cardPoints[ACE]=10;
  cardPoints[KING]=8;
  cardPoints[QUEEN]=7;
  cardPoints[JACK]=6;
  cardPoints[TEN]=5;
  cardPoints[NINE]=4.5;
  cardPoints[EIGHT]=4;
  cardPoints[SEVEN]=3.5;
  cardPoints[SIX]=3;
  cardPoints[FIVE]=2.5;
  cardPoints[FOUR]=2;
  cardPoints[THREE]=1.5;
  cardPoints[TWO]=1;

  handValue = cardPoints[highCard.value];

  if((highCard.value)==(lowCard.value)){
      if((highCard.value)<=2){
        handValue=5;
      }else{
        handValue = handValue*2;
      }
  }
  if((highCard.suit) == (lowCard.suit)){
    handValue = handValue + 2;
    }
  if(((highCard.value) == (lowCard.value)+1) || ((highCard.value) == ((lowCard.value)-1))){
    handValue = handValue + 1;
  }
  if(((highCard.value) == (lowCard.value)+2) || ((highCard.value) == ((lowCard.value)-2))){
    handValue = handValue - 1;
  }


    

    
    //if((*pckitr).value>=8){
    //  great=great+1;
    //}else{
    //  bad=bad+1;
    //}
  //}


  cout<<great<<" "<<good<< " "<<ok<<" "<<questionable<<" "<<bad<<endl;
  cout<<highCard.value<<endl;
  cout<< "Pocket Rateeee: " << handValue << endl;
  if(great==2){
    return 100;
  }else{
    return 10;
  }

}
//Great Pocket Cards:
  //Pocket Aces

  //One card is an Ace, and one card is above 10
    //Suited

    //Non-suited

  //Both cards are above 10
    //Suited

    //Non-Suited



//Good Pocket Cards:


//Ok Pocket Cards:


//Questionable Pocket Cards:


//"Bad" Pocket Cards:


