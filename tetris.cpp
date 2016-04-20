#include "tetris.h"

void rotate(PIECE &p) { //clockwise rotation
	switch (p.state) {
	case up:
		p.state = right;
		break;
	case right:
		p.state = down;
		break;
	case down:
		p.state = left;
		break;
	case left:
		p.state = up;
		break;
	}
}