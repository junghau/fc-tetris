#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"

void printPIECE_LOCATION(const PIECE &p);

int main() {
	
	//Assigning example testing piece
	PIECE test;
	test.index[0](2, 3);
	test.index[1](2, 2);
	test.index[2](1, 2);
	test.index[3](2, 4);
	test.shape = J;
	test.state = right;

	printPIECE_LOCATION(test);
	rotate(test);
	printPIECE_LOCATION(test);
	rotate(test);
	printPIECE_LOCATION(test);

	system("pause");
	return 0;
}

void printPIECE_LOCATION(const PIECE &p) {

	for (int i = 0; i <= 3; i++) {
		printf("(%d, %d)\n",p.index[i].x,p.index[i].y);
	}
	printf("\n");
}