#include "tetris.h"
#include "print.h"
#include <SoftwareSerial.h>
//Pins need numbering, functions need to be parameterised.

#define INTERRUPT1 2
#define INTERRUPT2 3
#define INTERVAL

#define LEFT
#define RIGHT
#define DOWN
#define ROTATE
#define RESETADDRESS //address for arduino reset
#define gameState_ROW_count 32

int gameState[8][gameState_ROW_count] = {0}; //gameState_ROW_count is defined as 19 in tetris.h
unsigned long previousMillis = 0;
int newPiece = 1;
PIECE currentPiece, oldPiece;
LedControl lc = LedControl(12, 11, 10, 4); //LedControl(dataPin,clockPin,csPin,numDevices)
int buttonPin = A0;
int buttonValue = 0;
int input; //saves the voltage value processed by the debouncing function
/*
    gameState: contains the positions of blocks that have settled in the playing field
    previousMillis: used to calculate amount of time before next cycle
    newPiece: boolean value tested to see if a new piece is required
    currentPiece: struct data that describes the piece that the user is in control of
*/

void (* resetFunc)(void) = RESETADDRESS; //reset function.
int debounce(void);

void setup(){ //initialises the pins to different modes

    int i;

    for(int index = 0; index < lc.getDeviceCount(); index++) { //sets each led panel to turn on
      lc.shutdown(index, false);
    }

    for(i = LEFT; i <= ROTATE; i++){
        pinMode(i, INPUT_PULLUP);
    }

}

void loop(){


  if(newPiece){ //provides a new piece to the user
      currentPiece = createPiece();
  }
  /*
  int upVal = digitalRead(ROTATE);
  int downVal = digitalRead(DOWN);
  int rightVal = digitalRead(RIGHT);
  int leftVal = digitalRead(LEFT);*/
  //note: interrupt may be better, will wait for prototype to see if necessary
  //might need to also move this above the the control flow,
  //for better polling effect.

  unsigned long currentMillis = millis(); //samples the current time

  if(currentMillis - previousMillis >= INTERVAL){ //tests to see if timer is up for next cycle
    previousMillis = currentMillis;

    newPiece = drop(currentPiece); //performs cycle
    updateScreen();

  }

  if(analogRead(buttonPin) < 1023){
    delay(10);
    int oldState = analogRead(buttonPin);
    delay(15)
    if(analogRead(buttonPin) == oldState){
        input = oldState;
    } else {
        input = -1;
    }
  }

  if(input == ROTATE){
      oldPiece = currentPiece;
      rotation_piece(currentPiece);
      updateScreen(currentPiece, oldPiece);
      input = -1;
  }

  else if(input == DOWN){
      oldPiece = currentPiece;
      newPiece = drop(currentPiece);
      updateScreen(currentPiece, oldPiece);
      input = -1;
  }

  else if(input == RIGHT){
      oldPiece = currentPiece;
      shift(currentPiece, 1);
      updateScreen(currentPiece, oldPiece);
      input = -1;
  }

  else if(input == LEFT){
      oldPiece = currentPiece;
      shift(currentPiece, -1);
      updateScreen(currentPiece, oldPiece);
      input = -1;
  }


  //Without debouncing
  /*int upVal = digitalRead(ROTATE); //Tests rotate pin
  if(upVal == HIGH){
      rotation_piece(currentPiece);
      updateScreen(currentPiece);
  }

  int downVal = digitalRead(DOWN); //Tests drop pin
  if(downVal == HIGH){
      newPiece = drop(currentPiece);
      updateScreen(currentPiece);

  }

  int rightVal = digitalRead(RIGHT); //Tests right pin
  if(rightVal == HIGH){
      shift(currentPiece ,1);
      updateScreen(currentPiece);
  }

  int leftVal = digitalRead(LEFT); //Tests left pin
  if(leftVal == HIGH){
      shift( currentPiece,-1);
      updateScreen(currentPiece);
  }*/
}
