#ifndef TEST_H
#define TEST_H

#include "tetris.h"
#include "noArduino.h"

//#define COLUMN_ROW //defined already in tetris.h
#define False 0
#define True 1

int wallTest(PIECE p/*, int direction*/);
inline int blockTest(PIECE &currentPiece);
inline int testRow(int row);


#endif
