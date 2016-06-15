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
#include <Arduino.h>
int address;
extern LedControl gameScreen;
extern LedControl scoreScreen;
extern int gameState[32][8];
extern int score;
extern int highScore;
bool newHighScore = false;

void updateScreen(const PIECE &currentPiece){

  int found;
  for (int row = 0; row < 32; row++) {
    for (int column = 0; column < 8; column++) {
      found = False;
      for(int i = 0; i < 4; i++){
        if(currentPiece.index[i].x == column && currentPiece.index[i].y == row){
          gameScreen.setLed(3 - row / 8, column, row % 8, True );
          found = True;
          break;
        }
      }

      if(!found){
        gameScreen.setLed(3 - row / 8, column, row % 8, gameState[row][column] );
      }
    }
  }

  scoreScreen.setDigit(0, 0, score % 10, false);
  scoreScreen.setDigit(0, 1, (score % 100) / 10, false);
  scoreScreen.setDigit(0, 2, (score % 1000)/ 100, false);
  scoreScreen.setDigit(0, 3, score / 1000, false);

  if(newHighScore) {
    scoreScreen.setDigit(0, 4, highScore % 10, false);
    scoreScreen.setDigit(0, 5, (highScore % 100) / 10, false);
    scoreScreen.setDigit(0, 6, (highScore % 1000)/ 100, false);
    scoreScreen.setDigit(0, 7, highScore / 1000, false);
  }
  

}
