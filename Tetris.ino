#include "tetris.h"
#include "print.h"
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <EEPROM.h>

#define INTERVAL 1000

#define LEFT 0
#define ROTATE 140
#define DOWN 322
#define RIGHT 500
#define RESET 736
#define NO_BUTTON 1023

#define M_FILTERSIZE 21
#define HIGH_SCORE_ADDRESS 0

uint16_t mfilter[M_FILTERSIZE];
uint8_t m_counter = 0;
bool button_press = false, button_release = false;
int qscompare(uint16_t a, uint16_t b);


int gameState[32][8] = {0}; //gameState_ROW_count is defined as 19 in tetris.h
unsigned long previousMillis = 0;
int newPiece = 1;
PIECE currentPiece, oldPiece;
LedControl gameScreen = LedControl(12, 11, 10, 4); //LedControl(dataPin,clockPin,csPin,numDevices)
LedControl scoreScreen = LedControl(7, 8 , 9, 1);

int buttonPin = A0;
int buttonValue = 0;
int input; //saves the voltage value processed by the debouncing function
int debugLED = 0;
int i;

int highScore = EEPROM.read(HIGH_SCORE_ADDRESS);

/*
    gameState: contains the positions of blocks that have settled in the playing field
    previousMillis: used to calculate amount of time before next cycle
    newPiece: boolean value tested to see if a new piece is required
    currentPiece: struct data that describes the piece that the user is in control of
*/

int debounce(void);

void setup(){ //initialises the pins to different modes
    Serial.begin(9600);

    int index;
    
    Serial.print("setup\n");
    for( index = 0; index < gameScreen.getDeviceCount(); index++) { //sets each led panel to turn on
      gameScreen.shutdown(index, false);
    }

    for( index = 0; index < scoreScreen.getDeviceCount(); index++){
      scoreScreen.shutdown(index, false);
    }
    pinMode(2, OUTPUT);
    Serial.print("setup done\n");

}

void loop(){

  //Serial.print("cycle\n");
  if(newPiece){ //provides a new piece to the user
      currentPiece = createPiece(random() % 6);
  }
  
  unsigned long currentMillis = millis(); //samples the current time

  if(currentMillis - previousMillis > INTERVAL){ //tests to see if timer is up for next cycle
    previousMillis = currentMillis;
    //Serial.print("timer\n");
    newPiece = drop(currentPiece); //performs cycle
    updateScreen(currentPiece);
    m_counter = 0;
    //Serial.print("Out of timer\n");
  }

 uint16_t button = analogRead(buttonPin), debounce = 0;

 if(button < ((NO_BUTTON + RESET) / 2)){
  if(m_counter < M_FILTERSIZE){
    mfilter[m_counter++] = analogRead(buttonPin);
  } else {
      button_press = true;      // Great! We have enough samples, let's register a button press
  }

  if (button_press && !button_release){
    button_release = true;

    qsort(mfilter, M_FILTERSIZE, sizeof(uint16_t), (int(*)(const void*, const void*))qscompare);

    input = mfilter[(M_FILTERSIZE + 1) / 2];

    if (input > ((RIGHT + DOWN) / 2)) { //Right
        shift(currentPiece, 1);
        updateScreen(currentPiece);
    }
    
    else if (input > ((DOWN + ROTATE) / 2)) { // Down
        newPiece = drop(currentPiece);
        updateScreen(currentPiece);
    }
    
    else if (input > ((ROTATE + LEFT) / 2)) { // Rotate
        rotation_piece(currentPiece);
        updateScreen(currentPiece);
    }
    
    else if (input < ((LEFT + ROTATE) / 2)) { // Left
        shift(currentPiece, -1);
        updateScreen(currentPiece);
    }
  }
 }
 else if(button_press) {
  m_counter = 0;
  button_press = false;
  button_release = false;
 }

}
 /*
  if(analogRead(buttonPin) < 1000){
    delay(10);
    int oldState = analogRead(buttonPin);
    delay(15);
    if(analogRead(buttonPin) == oldState){
        input = oldState;
    } else {
        input = -100;
    }
  }
  if(ROTATE - 20 <= input && input <= ROTATE + 20){

      rotation_piece(currentPiece);
      updateScreen(currentPiece);
      input = -100;
  }

  else if(DOWN - 20 <= input && input <= DOWN + 20){
 
      newPiece = drop(currentPiece);
      updateScreen(currentPiece);
      input = -100;
  }

  else if(RIGHT - 20 <= input && input <= RIGHT + 20){

      shift(currentPiece, 1);
      updateScreen(currentPiece);
      input = -100;
  }

  else if(LEFT - 20 <= input && input <= LEFT + 20){

      shift(currentPiece, -1);
      updateScreen(currentPiece);
      input = -100;
  }
  */


int qscompare(uint16_t a, uint16_t b) {
  if (a < b) {
    return -1;
  }

  if (a > b) {
    return 1;
  }

  return 0;
}
