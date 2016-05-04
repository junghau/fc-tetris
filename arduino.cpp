#include "tetris.h"
#include "print.h"

#include "noArduino.h"

//Pins need numbering, functions need to be parameterised.

#define INTERRUPT1 2
#define INTERRUPT2 3
#define INTERVAL
#define DRIVER1
#define DRIVER2

#define FIRST_LED_PIN
#define LAST_LED_PIN

#define LEFT
#define RIGHT
#define DOWN
#define ROTATE
#define RESETADDRESS //address for arduino reset

int gameState[8][gameState_ROW_count] = {0}; //gameState_ROW_count is defined as 19 in tetris.h
unsigned long previousMillis = 0;
int newPiece = 1;
PIECE currentPiece, previousPiece;

/*
    gameState: contains the positions of blocks that have settled in the playing field
    previousMillis: used to calculate amount of time before next cycle
    newPiece: boolean value tested to see if a new piece is required
    currentPiece: struct data that describes the piece that the user is in control of
*/

void (* resetFunc)(void) = RESETADDRESS; //reset function.

void setup(){ //initialises the pins to different modes

    int i;

    for(i = FIRST_LED_PIN; i <= LAST_LED_PIN; i++){
        pinMode(i, OUTPUT);
    }

    for(i = LEFT; i <= ROTATE; i++){
        pinMode(i, INPUT_PULLUP);
    }

    randomSeed(analogRead(0));

}

void loop(){


  if(newPiece){ //provides a new piece to the user
      previousPiece = currentPiece;
      currentPiece = createPiece();
      updateScreen(currentPiece, previousPiece);
      newPiece = 0;
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

    //noInterrupts(); //might be needed if interrupts are used
    previousPiece = currentPiece;
    newPiece = drop(currentPiece); //performs cycle
    updateScreen(currentPiece, previousPiece);

    //interrupts();
  }

  int upVal = digitalRead(ROTATE); //Tests rotate pin
  if(upVal == HIGH){
      previousPiece = currentPiece;
      rotation_piece(currentPiece);
      updateScreen(currentPiece, previousPiece);
  }

  int downVal = digitalRead(DOWN); //Tests drop pin
  if(downVal == HIGH){
      previousPiece = currentPiece;
      newPiece = drop(currentPiece);
      updateScreen(currentPiece, previousPiece);

  }

  int rightVal = digitalRead(RIGHT); //Tests right pin
  if(rightVal == HIGH){
      previousPiece = currentPiece;
      shift(currentPiece ,1);
      updateScreen(currentPiece, previousPiece);
  }

  int leftVal = digitalRead(LEFT); //Tests left pin
  if(leftVal == HIGH){
      previousPiece = currentPiece;
      shift( currentPiece,-1);
      updateScreen(currentPiece, previousPiece);
  }

}
