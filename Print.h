/*
    Function: Responsible for display of the tetris game states, and the update.
    Language: C
    Notes: 1)Assumes that the gamestate is represented by an 16x8 bitlist matrix
             Also assumes the pieces are a struct PIECE that contains AT LEAST the following data:

             struct PIECE {
             int coordinates [4][2]; where the first index accesses the (x,y) of each block of the piece.
             *other data*
             *other data*
            }


           2)WARNING: Use printState before printPiece! As the pieces are not ->
                      registered on the gamestate, using printState second would ->
                      result in the deletion of the piece from the screen.
           3)Parameters in the following functions are subject to change:
                i) void printState(void)
                ii) void printPiece(void)
*/

#include <LedControl>

#define ADDRESS <addr>

int previousPiece[4][2]; //saves the (x,y) of the previous piece to erase it before updating the screen to the new piece.

void printState(void){ //shows the current gamestate

    int row, column;

    for(row = 0, row < 16, row++){

        for (column = 0; column < 8, column++){
            if(gamestate[row][column] == 1){
                setLed(ADDRESS, row, column, TRUE);
            } else {
                setLed(ADDRESS, row, column, FALSE);
            }
        }

    }

}

void printPiece(void){

    int block;

    for (block = 0; block < 4; block++){

        setLed(ADDRESS, PIECE.coordinates[block][1], PIECE.coordinates[block][0], TRUE );

    }

}

void deletePiece(void){

    int block;

    for (block = 0; block < 4; block++){

        setLed(ADDRESS, previousPiece[1], previousPiece[0], FALSE );

    }

}

void update(void){

    //delete old piece off screen.
    //print new piece.

    printState();
    deletePiece();
    printPiece();

}
