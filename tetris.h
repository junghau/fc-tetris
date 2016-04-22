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

/*
	LOCATION struct is a alternative representation of a 2D-array
	Therefore x is considered as the row of a particular array, and y is considered as the column of a particular array.
	e.g. L.x and L.y is equivalent to the 2D-array of L[x][y]

	CAUTION!!! x and y do not work like the coordinate in a graph (where x is horizontal and y is vertical)
*/
struct LOCATION {
	int x;	//column
	int y;	//row
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
	PIECE operator=(const PIECE &x) {
		for (int i = 0; i < 4;i++)
			index[i] = x.index[i];
		state = x.state;
		shape = x.shape;
	}
};

//Funtion prototype
void rotate(PIECE &p);
bool compare(LOCATION centre, LOCATION x, LOCATION transformation);
inline void transform(LOCATION &buffer, LOCATION original, LOCATION transformation);

#endif