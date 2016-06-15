#include "test.h"
//#include <stdio.h>
/*
in main program:

int gamestate[8][16];

*/

int wallTest(const PIECE p/*, int direction*/) { //needs changing

	if (!(p.state % 2)) { //execute if state == 0, 2
		if(p.shape == 2) {
			if (p.index[0].x == 0 && p.state == 0){
				return 1;
			} else if (p.index[0].x == 7 && p.state == 2){
				return -1;
			} else {
				return 0;
			}
		} else if (p.shape <= 4) { //BLOCK 1

			if (p.index[0].x == 0) {
				//printf("returning 1\n");
				return 1;
			}
			else if (p.index[0].x == 7) {
				//printf("returning -1\n" );
				return -1;
			}
			else {
				//printf("returning 0\n");
				return 0;
			}

		} else if (p.shape == 5) { //BLOCK 2

			if (p.index[0].x == 0) {
				return 1;
			}
			else if (p.index[0].x >= 6) {
				return (5 - p.index[0].x);
			}
			else {
				return 0;
			}

		}
		else return 0;
	} else {
		return 0;
	}
}

int s_wallTest(const PIECE p){

	for(int i = 0; i < 4; i++){
		//printf("s_wallTest:%d\n" ,p.index[i].x );
		if(p.index[i].x == -1 || p.index[i].x == 8){
			return 0;
		}
	}

	return 1;

}

/*inline*/ int blockTest( PIECE &currentPiece){ //if no blocks, return true

    int i;

    for(i = 0; i < 4; i++){
        if(gameState[currentPiece.index[i].y][currentPiece.index[i].x] == 1){
            return 0;
        }
    }

    return 1;

}

inline int testRow(int row){

    int i;

    for(i = 0; i < 8; i++){
        if(gameState[row][i] == 0){
            return 0;
        }
    }
		//printf("Full row detected!\n");
    return 1;

}
