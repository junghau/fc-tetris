#include "tetris.h"
#define COLUMN_ROW
#define False 0
#define True 1

/*
in main program:

int gamestate[8][16];

*/

int testWall(int direction){ //needs changing

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

int testBlock(PIECE &currentPiece){

    int i;

    for(i = 0; i < 4; i++){
        if(gamestate[currentPiece.index[i].x][currentPiece.index[i].y] == 1){
            return False;
        }
    }

    return True;

}

void shift( PIECE &currentPiece , int direction){ //needs change

    PIECE potential = currentPiece;

    for(i = 0; i < 4; i++){

        potential.index[i].x += direction;

    }


    if(testBlock(direction)){

        currentPiece = potential;

    }

    return;
}

void rotation_piece(PIECE &currentPiece){

    int count;
    PIECE potential = currentPiece;

    shift(potential, testWall(potential));

    while(count = 0; count < 3; count++){

        rotate(potential);
        if(testBlock(potential)){
            currentPiece = potential;
            return;
        }
    }

    return;
}
