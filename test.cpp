#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include <iostream>

#define COLUMN_ROW

int gameState[16][8] = {0};

void printLocation(const PIECE &p);
void printVisual(const PIECE &p);

using namespace std;

int main(void){

  PIECE test = createPiece();

  int input, newPiece = 1;

  while(1){
    //system("CLS");

    if(newPiece){
      test = createPiece();
      newPiece = 0;
    }

    printLocation(test);
    printVisual(test);

    std::cin >> input;;

    if(input == 4){
      rotation_piece(test);

    } else if(input == 3){
      shift(test, 1);

    } else if(input == 2){
      newPiece = drop(test);

    } else if(input == 1){
      shift(test, -1);

    } else if(input == 0){
      printf("quitting\n");
      break;

    } else {
      printf("Error invalid input!\n");
    }
  }

  printf("terminated\n");

}

void printLocation(const PIECE &p){
  printf("new piece state\n");
  for(int i = 0; i < 4; i++){

    printf("x :%d, y :%d\n" ,p.index[i].x ,p.index[i].y);

  }

  printf("Shape :%d ,Orientation :%d\n" ,p.shape ,p.state);

}

void printVisual(const PIECE &p){

  for(int row = 15; row >= 0; row--){
    for(int column = 0; column < 8; column++){
      int block = 0;

      for(int i = 0; i < 4; i++){
        if(column == p.index[i].x && row == p.index[i].y){
          printf("X");
          block = 1;
          break;
        }
      }

      if(!block)
        printf("%d" ,gameState[row][column] );
    }

    printf("\n");
  }

}
