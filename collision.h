#include "test.h"
/*
in main program:

int gamestate[8][16];

*/

int wallTest(const PIECE p/*, int direction*/) { //needs changing

	if (!(p.state % 2)) {
		if (p.shape <= 4) { //BLOCK 1

			if (p.index[0].x == 0) {
				return 1;
			}
			else if (p.index[0].x == 7) {
				return -1;
			}
			else {
				return 0;
			}

		}
		else if (p.shape == 5) { //BLOCK 2

			if (p.index[0].x <= 1) {
				return 2 - p.index[0].x;
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

int s_wallTest(const PIECE p){

	for(int i = 0; i < 4; i++){
		if(p.index[i].x == 0 || p.index[i].x == 7){
			return 0;
		}
		return 1;
	}

}

/*inline*/ int blockTest( PIECE &currentPiece){

    int i;

    for(i = 0; i < 4; i++){
        if(gameState[currentPiece.index[i].column][currentPiece.index[i].row] == 1){
            return 0;
        }
    }

    return 1;

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
