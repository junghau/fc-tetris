#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include <iostream>

#define COLUMN_ROW

int gameState[16][8] = {0};

void printLocation(const PIECE &p);
void printVisual(void);

using namespace std;

int main(void){

  PIECE test;
  test = createPiece();

  int input;

  while(1){
    printLocation(test);
    printVisual();

    std::cin >> input;;

    if(input == 0){
      rotation_piece(test);

    } else if(input == 1){
      shift(test, 1);

    } else if(input == 2){
      drop(test);

    } else if(input == 3){
      shift(test, -1);

    } else if(input == 5){
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

void printVisual(void){

  for(int row = 15; row >= 0; row--){
    for(int column = 0; column < 8; column++){
      printf("%d" ,gameState[column][row] );
    }
    printf("\n");
  }

}
