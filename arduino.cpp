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

int gameState[8][19] = {0}
unsigned long previousMillis = 0;
int row, newPiece = 1;
SHAPE currentPiece;


void setup(){

    int i;

    for(i = FIRST_LED_PIN; i <= LAST_LED_PIN; i++){
        pinMode(i, OUTPUT);
    }

    for(i = LEFT; i <= ROTATE; i++){
        pinMode(i, INPUT_PULLUP);
    }

}

void loop(){


  if(newPiece){
      currentPiece = createPiece();
  }

  unsigned long currentMillis = millis();
  int upVal = digitalRead(ROTATE);
  int downVal = digitalRead(DOWN);
  int rightVal = digitalRead(RIGHT);
  int leftVal = digitalRead(LEFT);
  //note: interrupt may be better, will wait for prototype to see if necessary
  //might need to also move this above the the control flow, for better polling effect.


  if(currentMillis - previousMillis >= INTERVAL){
    previousMillis = currentMillis;
    //noInterrupts(); //might be needed if interrupts are used
    newPiece = drop(currentPiece);
    updateScreen();
    //interrupts();
  }

  if(upVal == HIGH){
      rotation_piece(currentPiece);
      updateScreen();
  }
  if(downVal == HIGH){
      newPiece = drop(currentPiece);
      updateScreen();

  }
  if(rightVal == HIGH){
      shift(currentPiece ,1);
      updateScreen();
  }
  if(leftVal == HIGH){
      shift( currentPiece,-1);
      updateScreen();
  }

}
