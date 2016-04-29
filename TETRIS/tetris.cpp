#include "tetris.h"

/*
La| Lb |Lc
----------
Ld|(Le)|Lf
----------
Lg| Lh |Li
*/

#ifdef RANDOM_BLOCK
enum loc
{
	La, Lb, Lc, Ld, Le, Lf, Lg, Lh, Li
};
#ifdef COLUMN_ROW
const LOCATION transformation_3x3[8] = { {2,0}	 //La->Lc
										,{0,2}	 //Lc->Li
										,{-2,0}	 //Li->Lg
										,{0,-2}	 //Lg->La
										,{1,1}	 //Lb->Lf
										,{-1,1}	 //Lf->Lh
										,{-1,-1} //Lh->Ld
										,{1,-1}	 //Ld->La
									};

//Location compared to the centre (Le)
const LOCATION loc_3x3[8] = {{-1,-1} //La
							,{1,-1}	 //Lc
							,{1,1}	 //Li
							,{-1,1}  //Lg
							,{0,-1}	 //Lb
							,{1,0}	 //Lf
							,{0,1}	 //Lh
							,{-1,0}	 //Ld
							};
#else
const LOCATION transformation_3x3[8] = { {0,2}	 //La->Lc
										,{2,0}	 //Lc->Li
										,{0,-2}  //Li->Lg
										,{-2,0}  //Lg->La
										,{1,1}	 //Lb->Lf
										,{1,-1}	 //Lf->Lh
										,{-1,-1} //Lh->Ld
										,{-1,1}	 //Ld->La
										};

//Location compared to the centre (Le)
const LOCATION loc_3x3[8] = { {-1,-1}  //La
							,{-1,1}	 //Lc
							,{1,1}	 //Li
							,{1,-1}  //Lg
							,{-1,0}	 //Lb
							,{0,1}	 //Lf
							,{1,0}	 //Lh
							,{0,-1}	 //Ld
							};
#endif

//Funtion prototype
loc getLOC(const PIECE &p, int i); //Get location in terms of Lx from coordinate by comparing to index[0]

void rotate(PIECE &p) { //clockwise rotation (-90 degree)
	LOCATION buffer[3];

	if (p.shape == O) { //Ignore square
		return;
	}else if (p.shape == I) {
		//				//
		//				//
		//later do this //
		//				//
		//				//
	}else {
		for (int i = 1; i <= 3; i++) {
			switch (getLOC(p,i)){
			case La:
				transform(buffer[i-1], p.index[i], transformation_3x3[0]);
				break;
			case Lc:
				transform(buffer[i-1], p.index[i], transformation_3x3[1]);
				break;
			case Li:
				transform(buffer[i-1], p.index[i], transformation_3x3[2]);
				break;
			case Lg:
				transform(buffer[i-1], p.index[i], transformation_3x3[3]);
				break;
			case Lb:
				transform(buffer[i-1], p.index[i], transformation_3x3[4]);
				break;
			case Lf:
				transform(buffer[i-1], p.index[i], transformation_3x3[5]);
				break;
			case Lh:
				transform(buffer[i-1], p.index[i], transformation_3x3[6]);
				break;
			case Ld:
				transform(buffer[i-1], p.index[i], transformation_3x3[7]);
				break;
			}
		}
		for (int i = 1; i <= 3;i++)
			p.index[i] = buffer[i-1];	//Copy buffer to current piece
	}

switch	(p.state) {
	case up:
		p.state = right;
		break;
	case right:
		p.state = down;
		break;
	case down:
		p.state = left;
		break;
	case left:
		p.state = up;
		break;
	}

}

loc getLOC(const PIECE &p, int i) {
	LOCATION centre(p.index[0]);
	for (int k = 0; k < 8; k++) {
		if (centre + loc_3x3[k] == p.index[i]) {
			switch (k) {
			case 0:
				return La;
			case 1:
				return Lc;
			case 2:
				return Li;
			case 3:
				return Lg;
			case 4:
				return Lb;
			case 5:
				return Lf;
			case 6:
				return Lh;
			case 7:
				return Ld;
			default:
				return La; //anything
			}
		}
	}
}

inline void transform(LOCATION &buffer, LOCATION original, LOCATION transformation) {
	buffer = original + transformation;
}

#else
#ifdef COLUMN_ROW
const LOCATION transformation[12] = {{2,0}	 //La->Lc
									,{1,-1}	 //Lb->Lf
									,{0,-2}	 //Lc->Li
									,{-1,-1}	 //Lf->Lh
									,{-2,0}	 //Li->Lg
									,{-1,1} //Lh->Ld
									,{0,2}	 //Lg->La
									,{1,1}	 //Ld->Lb
									,{2,-1}	 //special transform for I piece block 0
									,{1,0}	 //special transform for I piece block 1
									,{0,1}	 //special transform for I piece block 2
									,{-1,2}	 //special transform for I piece block 3
									};
#else
const LOCATION transformation[12] = {{0,-2}	 //La->Lc
									,{1,-1}	 //Lb->Lf
									,{2,0}	 //Lc->Li
									,{1,1}	 //Lf->Lh
									,{0,2}	 //Li->Lg
									,{-1,1} //Lh->Ld
									,{-2,0}	 //Lg->La
									,{-1,-1}	 //Ld->Lb
									,{-1,-2}	 //special transform for I piece block 0
									,{0,-1}	 //special transform for I piece block 1
									,{1,0}	 //special transform for I piece block 2
									,{2,1}	 //special transform for I piece block 3
									};
#endif

const int BLOCK_CONST[5][3] = { { 1, 4, 5 }, //L
								{ 1, 5, 6 }, //J
								{ 1, 3, 7 }, //T
								{ 1, 6, 7 }, //S
								{ 1, 3, 4 }  //Z
								};

const LOCATION initialIndex[7] = {  { 3, 12},
									{ 3,13 },
									{ 4,13 },
									{ 3,14 },
									{ 4,14 },
									{ 3,15 },
									{ 4,15 }
								};
const int shape_specific_index[7][4] = {
										{3, 5, 2,1},
										{2, 6, 2, 1},
										{3, 5, 4,1},
										{3, 5, 4, 2},
										{4, 6, 1,3},
										{5, 3, 1,0},
										{5, 6, 3, 4}
}

void rotate(PIECE &currentPiece) {

	int block, access;

	if (currentPiece.shape <= 4) {
		for (block = 1; block <= 3; block++) { //could have done it in one line, but too long for readability/presentation.
			access = (BLOCK_CONST[currentPiece.shape][block] + 2 * currentPiece.state) % 8;
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

	currentPiece.state = static_cast<ORIENTATION>((currentPiece.state + 1) % 4); //Hope it works

	return;

}
#endif

int drop(PIECE &currentPiece){

	PIECE potentialPiece = currentPiece;
	int i;

	for(i = 0; i < 4; i++){
		if(potentialPiece.index[i].row-- == 0){
			settle(currentPiece);
			return 1;
		}
	}

	if(blockTest(potentialPiece)){
		currentPiece = potentialPiece;
		return 0;
	}

	else {
		settle(currentPiece);
		return 0;
	}
}

void settle(PIECE &currentPiece){

	int i;


	for(i = 0; i < 4; i++){
		if(currentPiece.index[i].row >= 16){
			gameOver();
		}
		gameState[currentPiece.index[i].column][currentPiece.index[i].row] = 1;
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

    shift(potential, testWall(potentialPiece));

    while(count = 0; count < 3; count++){

        rotate(potentialPiece);
        if(testBlock(potentialPiece)){
            currentPiece = potentialPiece;
            return;
        }
    }

    return;
}

void shift( PIECE &currentPiece , int direction){ //needs change

    PIECE potentialPiece = currentPiece;

    for(i = 0; i < 4; i++){

        potentialPiece.index[i].column += direction;

    }


    if(testBlock(direction)){

        currentPiece = potentialPiece;

    }

    return;
}

void deleteRow(int row){

	int row = 0, column = 0, block = 0, emptyRow = 0;

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

	return;

}

PIECE createPiece(void){

	int i;
	PIECE currentPiece;

	currentPiece.shape = random(8);

	for(i = 0; i < 4; i++){
		currentPiece.index[i] = initialIndex[shape_specific_index[currentPiece.shape][i]];
	}

	currentPiece.state = 0;

	return currentPiece;
}

void gameOver(void){

	while(1){
		if(digitalRead(ROTATE) == HIGH){
			break;
		}
	}
	//placeholder for code to signify game over

	resetFunc();

}
