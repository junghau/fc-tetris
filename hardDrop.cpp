#include "tetris.h"
#include "test.h"
#include "collision.h"
#include <stdlib.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <EEPROM.h>

/*
La| Lb |Lc
----------
Ld|(Le)|Lf
----------
Lg| Lh |Li
*/

void (* resetFunc)(void) = 0;

extern int buttonPin;
int score = 0;
extern int highScore;
extern bool newHighScore;
extern bool swapLimitMet;

const LOCATION transformation[12] = {
									{2, 0}	 //La->Lc
									,{1, -1}	 //Lb->Lf
									,{0, -2}	 //Lc->Li
									,{-1, -1}	 //Lf->Lh
									,{-2, 0}	 //Li->Lg
									,{-1, 1} //Lh->Ld
									,{0, 2}	 //Lg->La
									,{1, 1}	 //Ld->Lb
									,{2, -1}	 //special transform for I piece block 0
									,{1, 0}	 //special transform for I piece block 1
									,{0, 1}	 //special transform for I piece block 2
									,{-1, 2}	 //special transform for I piece block 3
									};

const int BLOCK_CONST[5][3] = {
								{ 1, 4, 5}, //L
								{ 1, 5, 6}, //J
								{ 1, 3, 5}, //T
								{ 1, 3, 4}, //S
								{ 1, 6, 7}  //Z
								};

LOCATION initialIndex[7] = {
									{ 3, 24},
									{ 3, 25},
									{ 4, 25},
									{ 3, 26},
									{ 4, 26},
									{ 3, 27},
									{ 4, 27}
								};
int shape_specific_index[7][4] = {
										{3, 5, 2, 1},
										{4, 6, 2, 1},
										{3, 5, 4, 1},
										{3, 5, 4, 2},
										{4, 6, 1, 3},
										{5, 3, 1, 0},
										{5, 6, 3, 4}
};

void rotate(PIECE &currentPiece) {

	int block, access;

	if (currentPiece.shape <= 4) {
		for (block = 1; block <= 3; block++) { //could have done it in one line, but too long for readability/presentation.
			access = (BLOCK_CONST[currentPiece.shape][block - 1] + 2 * currentPiece.state) % 8;
			//printf("access is :%d\n" ,access);
			currentPiece.index[block] = currentPiece.index[block] + transformation[access];
		}
	}
	else if (currentPiece.shape == 5) {
		if (!(currentPiece.state % 2)) {
			for (block = 0; block < 4; block++) {
				currentPiece.index[block] = currentPiece.index[block] + transformation[block + 8];
			}
		}
		else {
			for (block = 0; block < 4; block++) {
				currentPiece.index[block] = currentPiece.index[block] - transformation[block + 8];
			}
		}
	}

	currentPiece.state = static_cast<ORIENTATION>((currentPiece.state + 1) % 4);

}

int drop(PIECE &currentPiece){

	int i;

	//printf("entered drop\n");
  PIECE potentialPiece;

	for(int i = 0; i < 4; i++){
		potentialPiece.index[i].x = currentPiece.index[i].x;
		potentialPiece.index[i].y = currentPiece.index[i].y;
	}

	potentialPiece.shape = currentPiece.shape;
	potentialPiece.state = currentPiece.state;


	while(blockTest(potentialPiece)){
    for(i = 0; i < 4; i++){

  		potentialPiece.index[i].y = potentialPiece.index[i].y - 1;

  		if(potentialPiece.index[i].y < 0){
        for(int i = 0; i < 4; i++){
      		currentPiece.index[i].y = potentialPiece.index[i].y + 1;
      	}
  			settle(currentPiece);
        return 1;
  		}
  	}
	}

  for(int i = 0; i < 4; i++){
    currentPiece.index[i].y = potentialPiece.index[i].y + 1;
  }
	settle(currentPiece);
	return 1;
	}
}

void settle(PIECE &currentPiece){

	int i;


	for(i = 0; i < 4; i++){
		if(currentPiece.index[i].y >= 23){
      //Serial.print("game over\n");
			gameOver();
		}
		//printf("settling (%d, %d)\n" ,currentPiece.index[i].x ,currentPiece.index[i].y);
		gameState[currentPiece.index[i].y][currentPiece.index[i].x] = 1;
	}

	int deleted = 0;

	for(i = 0; i < 4; i++){
		//printf("settle : testing row %d\n" ,currentPiece.index[i].y );
		while(testRow(currentPiece.index[i].y)){
			//printf("tested row once. %d\n" ,currentPiece.index[i].y);
			deleteRow(currentPiece.index[i].y);
			score++;
	  }
	}

 if(score > highScore){
  highScore = score;
 }

}

void rotation_piece(PIECE &currentPiece){

  int count;
	PIECE potentialPiece;

	for(int i = 0; i < 4; i++){
		potentialPiece.index[i].x = currentPiece.index[i].x;
		potentialPiece.index[i].y = currentPiece.index[i].y;
	}

	potentialPiece.shape = currentPiece.shape;
	potentialPiece.state = currentPiece.state;

    shift(potentialPiece, wallTest(potentialPiece));

    for(count = 0; count < 3; count++){

        rotate(potentialPiece);
        if(blockTest(potentialPiece)){
					currentPiece = potentialPiece;
          return;
        }
    }

    return;
}

/*inline*/ void shift(PIECE &currentPiece , int direct){

		PIECE potentialPiece;

		for(int i = 0; i < 4; i++){
			potentialPiece.index[i].x = currentPiece.index[i].x;
			potentialPiece.index[i].y = currentPiece.index[i].y;
		}

		potentialPiece.shape = currentPiece.shape;
		potentialPiece.state = currentPiece.state;


		//printf("entering shift\n");
    for(int i = 0; i < 4; i++){

        potentialPiece.index[i].x += direct;
				//printf("%d\n" ,potentialPiece.index[i].x );
				//printf("original %d\n" ,currentPiece.index[i].x );
    }


    if(blockTest(potentialPiece) && s_wallTest(potentialPiece)){
				//printf("shifted\n");
        currentPiece = potentialPiece;
				return;
    }

		//printf("failed\n");

		return;
}

/*inline*/ void deleteRow(int row){


	while(row < 23){
		for(int column = 0; column < 8; column++ ){
			gameState[row][column] = gameState[row + 1][column];
		}
		row++;
	}

}

PIECE createPiece(SHAPE shape){

	int i;
	PIECE currentPiece;

	currentPiece.shape =  (shape);
  //currentPiece.state = static_cast<ORIENTATION>(random() % 4);
	for(i = 0; i < 4; i++){
		currentPiece.index[i] = initialIndex[shape_specific_index[currentPiece.shape][i]];
	}
x
  swapLimitMet = false;

	return currentPiece;
}

/*inline*/ void gameOver(void){

  if(newHighScore){
    EEPROM.write(0, score);
  }

	while(1){
		if( analogRead(buttonPin) < 736 ) {
      resetFunc();
		}
	}

}
