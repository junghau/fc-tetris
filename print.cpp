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

#include "print.h"

#define ADDRESS <addr>

inline void printState(void){ //shows the current gamestate

	for (int row = 0; row < 16; row++) {

		for (int column = 0; column < 8; column++) {
            if(gameState[row][column] == 1){
                setLed(ADDRESS, row, column, TRUE);
            } else {
                setLed(ADDRESS, row, column, FALSE);
            }
        }

    }

}

inline void printPiece(const PIECE &p){

    int block;

    for (block = 0; block < 4; block++){

        setLed(ADDRESS, p.index[block].row, p.index[block].column, TRUE );

    }

}

inline void deletePiece(const PIECE &p){

    int block;

    for (block = 0; block < 4; block++){

        setLed(ADDRESS, p.index[block].r, p.index[block].c, FALSE );

    }

}

inline void updateScreen(const PIECE &currentPiece, const PIECE &previousPiece){

    //delete old piece off screen.
    //print new piece.

    printState();
    deletePiece(previousPiece);
    printPiece(currentPiece);

}
