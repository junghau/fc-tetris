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
	int row, column;

	/*
	**********THE POWER OF AMPERSAND ALIAS(&)**********
	For your convenience, I have added the following: 
	Now, row can be accessed with row, r, or x, and column can be accessed with column, c, or y
	Therefore (x == r == row) and also (y == c == column)
	*/
	
	int &x = row;	//row
	int &r = row;	//row
	int &y  = column;	//column
	int &c = column;	//column

	//LOCATION() :x{0}, y{0} {}
	LOCATION(int a = 0, int b = 0) {
		LOCATION::x = a;
		LOCATION::y = b;
	}
	LOCATION operator()(int a, int b) { //overload () operator to enable easy (x,y) assignment
		LOCATION::x = a;
		LOCATION::y = b;
		return *this;
	}
	LOCATION operator=(LOCATION L) {
		LOCATION::x = L.x;
		LOCATION::y = L.y;
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
	PIECE operator=(const PIECE &p) {
		for (int i = 0; i < 4;i++)
			index[i] = p.index[i];
		state = p.state;
		shape = p.shape;
	}
};

//Funtion prototype
void rotate(PIECE &p);
bool compare(LOCATION centre, LOCATION x, LOCATION transformation);
inline void transform(LOCATION &buffer, LOCATION original, LOCATION transformation);

#endif