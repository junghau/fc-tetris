#ifndef PRINT_H
#define PRINT_H

#include <LedControl>
#include "tetris.h"

#include "noArduino.h"

#define TRUE 1
#define FALSE 0

inline void printState(void);
inline void printPiece(const PIECE &p);
inline void deletePiece(void);
inline void updateScreen(const PIECE &p);

#endif
