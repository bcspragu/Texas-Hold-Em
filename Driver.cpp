#include "Dealer.h"
#include "Table.h"

int main(){
  Dealer d;
  Table t;
  
  while(true){
    t.drawBoard(&d);
  }
  return 0;
}
