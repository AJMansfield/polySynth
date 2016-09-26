#include "error.h"

void flash(){
  digitalWrite(13, !digitalRead(13));
  delay(10);
  digitalWrite(13, !digitalRead(13));
}

void error(int i){
  while(true){
    for(int j = 0; j < i; j++){
      flash();
      delay(100);
    }
    delay(400);
  }
}