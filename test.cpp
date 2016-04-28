#include "tetris.h"
#define COLUMN_ROW
#define False 0
#define True 1

/*
in main program:

int gamestate[8][16];

*/

int wallTest(int direction){ //needs changing

    if(!(p.ORIENTATION % 2)){
        if(p.SHAPE <= 4){ //BLOCK 1

            if(p.index[0].x == 0){
                return 1;
            } else if (p.index[0].x == 8) {
                return -1;
            } else {
                return 0;
            }

        } else if (p.SHAPE == 5){ //BLOCK 2

            if(p.index[0].x <= 1 ){
                return 2 - p.index[0]
            } else if(p.index[0].x == 8){
                return -1;

            } else {
                return 0;
            }

        }

    else return 0;
}

int blockTest(PIECE &currentPiece){

    int i;

    for(i = 0; i < 4; i++){
        if(gamestate[currentPiece.index[i].column][currentPiece.index[i].row] == 1){
            return False;
        }
    }

    return True;

}

int testRow(int row){

    int i;

    for(i = 0; i < 8; i++){
        if(gameState[i][16] == 0){
            return 0;
        }
    }

    return 1;

}
