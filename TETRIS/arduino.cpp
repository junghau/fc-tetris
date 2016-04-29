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

int gameState[8][16 /*19*/] = {0};
unsigned long previousMillis = 0;
int newPiece = 1;
SHAPE currentPiece;

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

    //noInterrupts(); //might be needed if interrupts are used

    newPiece = drop(currentPiece); //performs cycle
    updateScreen();

    //interrupts();
  }

  int upVal = digitalRead(ROTATE); //Tests rotate pin
  if(upVal == HIGH){
      rotation_piece(currentPiece);
      updateScreen();
  }

  int downVal = digitalRead(DOWN); //Tests drop pin
  if(downVal == HIGH){
      newPiece = drop(currentPiece);
      updateScreen();

  }

  int rightVal = digitalRead(RIGHT); //Tests right pin
  if(rightVal == HIGH){
      shift(currentPiece ,1);
      updateScreen();
  }

  int leftVal = digitalRead(LEFT); //Tests left pin
  if(leftVal == HIGH){
      shift( currentPiece,-1);
      updateScreen();
  }

}
