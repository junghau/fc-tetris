#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"

int main() {
	
	//Assigning example testing piece
	PIECE test;
	test.index[0](2, 3);
	test.index[1](2, 2);
	test.index[2](1, 2);
	test.index[3](2, 4);
	test.shape = J;
	test.state = right;

	rotate(test);
	rotate(test);
	//printf("%d\n",test.index[2].x);

	system("pause");
	return 0;
}

