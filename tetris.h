#ifndef TETRIS_H
#define TETRIS_H

#define xLEN 8
#define yLEN 16

void rotate(PIECE &);

typedef enum {
	up = 1, right, down, left //the direction of the top of the piece is pointing to
}ORIENTATION;

typedef enum {
	I = 1, J, L, O, S, T, Z
}SHAPE;

struct LOCATION {
	int x;
	int y;
	LOCATION() :x{0}, y{0} {}
	LOCATION operator()(int x, int y) { //overload () operator to enable easy (x,y) assignment
		LOCATION::x = x;
		LOCATION::y = y;
		return *this;
	}
};

struct PIECE {
	LOCATION index[4];
	ORIENTATION state;
	SHAPE shape;
	PIECE() :state{up}, shape{I} {} //initializer
};

#endif