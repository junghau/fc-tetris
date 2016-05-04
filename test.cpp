#include "test.h"
/*
in main program:

int gamestate[8][16];

*/

int wallTest(PIECE p/*, int direction*/) { //needs changing

	if (!(p.state % 2)) {
		if (p.shape <= 4) { //BLOCK 1

			if (p.index[0].x == 0) {
				return 1;
			}
			else if (p.index[0].x == 8) {
				return -1;
			}
			else {
				return 0;
			}

		}
		else if (p.shape == 5) { //BLOCK 2

			if (p.index[0].x <= 1) {
				return 2; //don't know what to correct since don't know what this is...
			}
			else if (p.index[0].x == 8) {
				return -1;

			}
			else {
				return 0;
			}

		}

		else return 0;
	}
}

inline int blockTest(PIECE &currentPiece){

    int i;

    for(i = 0; i < 4; i++){
        if(gameState[currentPiece.index[i].column][currentPiece.index[i].row] == 1){
            return False;
        }
    }

    return True;

}

inline int testRow(int row){

    int i;

    for(i = 0; i < 8; i++){
        if(gameState[i][16] == 0){
            return 0;
        }
    }

    return 1;

}