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
  int value1=0;
  int value2=0;
  int suit1=0;
  int suit2=0;

  std::vector<Card>::iterator pckitr;
   
   for(pckitr = hand.begin(); pckitr != hand.end(); ++pckitr){
    if(counter==0){
      value1= (*pckitr).value;
      suit1=(*pckitr).suit;
      counter++;
    }else if(counter==1){
      value2=(*pckitr).value;
      suit2=(*pckitr).suit;
    }
    }
    cout<<value1<<endl;
    cout<<value2<<endl;
    cout<<suit1<<endl;
    cout<<suit2<<endl;

    //if((*pckitr).value>=8){
    //  great=great+1;
    //}else{
    //  bad=bad+1;
    //}
  //}
  cout<<great<<" "<<good<< " "<<ok<<" "<<questionable<<" "<<bad<<endl;
  
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


