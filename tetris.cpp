#include "tetris.h"
#include "test.h"
#include "collision.h"
#include <stdlib.h>
#include <stdio.h>
/*
La| Lb |Lc
----------
Ld|(Le)|Lf
----------
Lg| Lh |Li
*/

const LOCATION transformation[12] = {{2, 0}	 //La->Lc
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
								{ 1, 3, 7}, //T
								{ 1, 6, 7}, //S
								{ 1, 3, 4}  //Z
								};

const LOCATION initialIndex[7] = {
									{ 3, 12},
									{ 3, 13},
									{ 4, 13},
									{ 3, 14},
									{ 4, 14},
									{ 3, 15},
									{ 4, 15}
								};
const int shape_specific_index[7][4] = {
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
			printf("access is :%d\n" ,access);
			currentPiece.index[block] = currentPiece.index[block] + transformation[access];
		}
	}
	else if (currentPiece.shape == 5) {
		if (currentPiece.state == 0) {
			for (block = 0; block < 4; block++) {
				currentPiece.index[block] = currentPiece.index[block] + transformation[block + 7];
			}
		}
		else {
			for (block = 0; block < 4; block++) {
				currentPiece.index[block] = currentPiece.index[block] - transformation[block + 7];
			}
		}
	}

	currentPiece.state = static_cast<ORIENTATION>((currentPiece.state + 1) % 4);

}

int drop(PIECE &currentPiece){

	PIECE potentialPiece;

	for(int i = 0; i < 4; i++){
		potentialPiece.index[i].x = currentPiece.index[i].x;
		potentialPiece.index[i].y = currentPiece.index[i].y;
		potentialPiece.shape = currentPiece.shape;
		potentialPiece.state = currentPiece.state;
	}

	int i;

	printf("entered drop\n");

	for(i = 0; i < 4; i++){
		potentialPiece.index[i].y -= 1;
		printf("%d\n", potentialPiece.index[i].y);
		if(potentialPiece.index[i].y < 0){
			settle(currentPiece);
			printf("hit bottom\n");
			return 1;
		}
	}

	if(blockTest(potentialPiece)){
		currentPiece = potentialPiece;
		printf("dropped\n");

		return 0;
	}

	else {
		settle(currentPiece);
		printf("hit block\n");
		return 0;
	}
}

void settle(PIECE &currentPiece){

	int i;


	for(i = 0; i < 4; i++){
		if(currentPiece.index[i].row >= 16){
			gameOver();
		}
		gameState[currentPiece.index[i].row][currentPiece.index[i].column] = 1;
	}

	for(i = 0; i < 4; i++){
		if(testRow(currentPiece.index[i].column)){
			deleteRow(currentPiece.index[i].column);
		}
	}

}

void rotation_piece(PIECE &currentPiece){

    int count;
    PIECE potentialPiece = currentPiece;

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

/*inline*/ void shift(PIECE &currentPiece , int direction){

    PIECE potentialPiece;

		for(int i = 0; i < 4; i++){
			potentialPiece.index[i].x = currentPiece.index[i].x;
			potentialPiece.index[i].y = currentPiece.index[i].y;
			potentialPiece.shape = currentPiece.shape;
			potentialPiece.state = currentPiece.state;
		}

		printf("entering shift\n");
    for(int i = 0; i < 4; i++){

        potentialPiece.index[i].x += direction;
				printf("%d\n" ,potentialPiece.index[i].x );
				printf("original %d\n" ,currentPiece.index[i].x );
    }


    if(blockTest(potentialPiece) && s_wallTest(potentialPiece)){
				printf("shifted\n");
        currentPiece = potentialPiece;
				return;
    }

		printf("failed\n");

		return;
}

/*inline*/ void deleteRow(int row){

	int column = 0, block = 0, emptyRow = 0;

	while(row-- < 16){
		emptyRow = 0;
		for(column = 0; column < 16; column++ ){
			gameState[row][column] = gameState[row - 1][column];
			if(gameState[row - 1][column] == 1){
				emptyRow = 1;
			}
			if(emptyRow){
				return;
			}
		}
	}

}

PIECE createPiece(void){

	int i;
	PIECE currentPiece;

	//currentPiece.shape = static_cast<SHAPE>(random(6));
	currentPiece.shape = J;
	for(i = 0; i < 4; i++){
		currentPiece.index[i] = initialIndex[shape_specific_index[currentPiece.shape][i]];
	}

	currentPiece.state = up;

	return currentPiece;
}

/*inline*/ void gameOver(void){

	while(1){
		if(0/*digitalRead(ROTATE) == HIGH*/){
			break;
		}
	}
	//placeholder for code to signify game over
	printf("placeholder, game end: resetFunc()\n");
	//resetFunc();

}
