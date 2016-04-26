#include "tetris.h"

/*
0_|_1__|_2_
La| Lb |Lc|	0
--------------
Ld|(Le)|Lf| 1
--------------
Lg| Lh |Li| 3

*/

const LOCATION transformation_3x3[12] = { 										 {2, 0}	 //La->Lc
																				,{1, 1}	 //Lb->Lf
																				,{0, 2}	 //Lc->Li
																				,{-1,1}	 //Lf->Lh
																				,{-2,0}	 //Li->Lg
																				,{-1,-1} //Lh->Ld
																				,{0,-2}	 //Lg->La
																				,{1,-1}	 //Ld->Lb
																				,{2,-1}	 //special transform for I piece block 0
																				,{1, 0}	 //special transform for I piece block 1
																				,{0, 1}	 //special transform for I piece block 2
																				,{-1,2}	 //special transform for I piece block 3
																			};


const int list[5][3] = {
																						{ 1, 4, 5}, //L
																						{ 1, 5, 6}, //J
																						{ 1, 3, 7}, //T
																						{ 1, 2, 7}, //S
																						{ 1, 0, 3}  //Z
}

void rotate(PIECE &p){

	int block, access;

	if(p.shape <= 4){
		for(block = 1; block <= 3; block++){ //could have done it in one line, but too long for readability/presentation.
			access = ( list[p.shape][block] + 2 * p.orientation ) % 8;
			p.index[block] = p.index[block] + transformation_3x3[access];
		}
	} else if (p.shape == 5){
		if(p.orientation == 0){
			for(block = 0; block < 4; block++){
				p.index[block] = p.index[block] + transformation_3x3[block + 7]
			}
		} else {
			for(block = 0; block < 4; block++){
				p.index[block] = p.index[block] - transformation_3x3[block + 7]
			}
		}
	}

	p.orientation = (p.orientation++ % 4);

	return;

}
