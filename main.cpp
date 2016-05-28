#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"

void printPIECE_LOCATION(const PIECE &p);
void printPIECE_GRAPHIC(const PIECE &p);

int main() {
	
	//Assigning example testing piece
	PIECE test;
	test.index[0](3, 2);
	test.index[1](4, 2);
	test.index[2](2, 2);
	test.index[3](2, 1);
	test.shape = J;
	test.state = right;

	printPIECE_LOCATION(test);
	printPIECE_GRAPHIC(test);

	//Four rotation should be equal to the original state
	rotate(test);
	rotate(test);
	rotate(test);
	rotate(test);

	printPIECE_LOCATION(test);
	printPIECE_GRAPHIC(test);

	system("pause");
	return 0;
}

void printPIECE_LOCATION(const PIECE &p) {

	for (int i = 0; i <= 3; i++) {
		printf("(%d, %d)\n",p.index[i].x,p.index[i].y);
	}
	printf("\n");
}

void printPIECE_GRAPHIC(const PIECE &p) {
	int matrix[4][4] = { {0} };

	LOCATION piece[4];
	for (int i = 0; i < 4;i++) {
		piece[i] = p.index[i];
	}

	int rmin = piece[0].r, cmin = piece[0].c;

	for (int i = 1; i < 4;i++) {
		if (rmin > piece[i].r)
			rmin = piece[i].r;
		if (cmin > piece[i].c)
			cmin = piece[i].c;
	}
	for (int i = 0; i < 4;i++) {
		piece[i].r -= rmin;
		piece[i].c -= cmin;
	}

	if (p.shape == O) {
			printf("1 1\n1 1\n");
			return;
	}else if (p.shape == I) {
		for (int i = 0;i <= 3;i++) {
			matrix[piece[i].r][piece[i].c] = 1;
		}
	}else {
		matrix[1][1] = 1;
		for (int i = 1;i <= 3;i++) {
			matrix[piece[i].r][piece[i].c] = 1;
		}
	}

	if (p.shape == I) {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				printf("%d ",matrix[i][j]);
			}
			printf("\n");
		}
	}else {
		for (int i = 0;i < 3;i++) {
			for (int j = 0;j < 3;j++) {
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}