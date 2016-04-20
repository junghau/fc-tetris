#ifndef TETRIS_H
#define TETRIS_H

#define xLEN 8
#define yLEN 16



typedef enum {
	up = 1, right, down, left //the direction of the top of the piece is pointing to
}ORIENTATION;

typedef enum {
	I = 1, J, L, O, S, T, Z
}SHAPE;

struct LOCATION {
	int x;
	int y;
	//LOCATION() :x{0}, y{0} {}
	LOCATION(int x = 0, int y = 0) {
		LOCATION::x = x;
		LOCATION::y = y;
	}
	LOCATION operator()(int x, int y) { //overload () operator to enable easy (x,y) assignment
		LOCATION::x = x;
		LOCATION::y = y;
		return *this;
	}
	LOCATION operator=(LOCATION x) {
		LOCATION::x = x.x;
		LOCATION::y = x.y;
		return *this;
	}
};

inline bool operator==(LOCATION a, LOCATION b) {
	if (a.x == b.x && a.y == b.y)
		return true;
	else
		return false;
}

struct PIECE {
	LOCATION index[4]; //index[0] should always be the center of the 3x3 piece
	ORIENTATION state;
	SHAPE shape;
	PIECE() :state{up}, shape{I} {} //initializer
	PIECE operator=(PIECE x) {
		for (int i = 0; i < 4;i++)
			index[i] = x.index[i];
		state = x.state;
		shape = x.shape;
	}
};


void rotate(PIECE &p);
bool compare(LOCATION centre, LOCATION x, LOCATION transformation);
inline void transform(LOCATION &buffer, LOCATION original, LOCATION transformation);

#endif