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

//lc.setLed(panel, col, panelRow, true);
//void lc.setLed(int addr, int col, int row, boolean state);
#include "print.h"

int address;

inline void printState(void){ //shows the current gamestate

	for (int row = 0; row < 16; row++) {

		for (int column = 0; column < 8; column++) {
            if(gameState[column][row] == 1){
                setLed(ADDRESS, column, row, True);
            } else {
                setLed(ADDRESS, column, row, False);
            }
        }

    }

}

inline void printPiece(const PIECE &p){

    int block;

    for (block = 0; block < 4; block++){

        setLed(ADDRESS, p.index[block].column, p.index[block].row, True );

    }

}

inline void deletePiece(const PIECE &p){

    int block;

    for (block = 0; block < 4; block++){

        setLed(ADDRESS, p.index[block].column, p.index[block].row, False );

    }

}

inline void updateScreen(const PIECE &newPiece, const PIECE &oldPiece){

    //delete old piece off screen.
    //print new piece.

    printState();
    deletePiece(oldPiece);
    printPiece(newPiece);

}
