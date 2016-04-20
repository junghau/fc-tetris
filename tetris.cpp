#include "tetris.h"


/*
La| Lb |Lc
----------
Ld|(Le)|Lf
----------
Lg| Lh |Li
*/
enum loc
{
	La, Lb, Lc, Ld, Le, Lf, Lg, Lh, Li
};

LOCATION transformation_3x3[8] = { {0,2}	 //La->Lc
									,{2,0}	 //Lc->Li
									,{0,-2}  //Li->Lg
									,{-2,0}  //Lg->La
									,{1,1}	 //Lb->Lf
									,{1,-1}	 //Lf->Lh
									,{-1,-1} //Lh->Ld
									,{-1,1}	 //Ld->La
									};

//Location compared to the centre (Le)
LOCATION loc_3x3[8] = { {-1,-1}  //La
						,{-1,1}	 //Lc
						,{1,1}	 //Li
						,{1,-1}  //Lg
						,{-1,0}	 //Lb
						,{0,1}	 //Lf
						,{1,0}	 //Lh
						,{0,-1}	 //Ld
						};


loc getLOC(PIECE p, int i);

void rotate(PIECE &p) { //clockwise rotation
	LOCATION buffer[4];
	buffer[0](p.index[0].x, p.index[0].y);

	if (p.shape == O) { //Ignore square
		return;
	}else if (p.shape == I) {
		//				//
		//				//
		//later do this //
		//				//
		//				//
	}else {
		for (int i = 1; i <= 3; i++) {
			switch (getLOC(p,i)){
			case La:
				transform(buffer[i], p.index[i], transformation_3x3[0]);
				break;
			case Lc:
				transform(buffer[i], p.index[i], transformation_3x3[1]);
				break;
			case Li:
				transform(buffer[i], p.index[i], transformation_3x3[2]);
				break;
			case Lg:
				transform(buffer[i], p.index[i], transformation_3x3[3]);
				break;
			case Lb:
				transform(buffer[i], p.index[i], transformation_3x3[4]);
				break;
			case Lf:
				transform(buffer[i], p.index[i], transformation_3x3[5]);
				break;
			case Lh:
				transform(buffer[i], p.index[i], transformation_3x3[6]);
				break;
			case Ld:
				transform(buffer[i], p.index[i], transformation_3x3[7]);
				break;
			}
		}
		for (int i = 0; i < 4;i++)
			p.index[i] = buffer[i];	//Copy buffer to current piece
	}
	
switch	(p.state) {
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

loc getLOC(PIECE p, int i) {
	LOCATION centre(p.index[0].x, p.index[0].y);
	for (int k = 0; k < 8; k++) {
		if (compare(centre, p.index[i], loc_3x3[k])) {
			switch (k) {
			case 0:
				return La;
			case 1:
				return Lc;
			case 2:
				return Li;
			case 3:
				return Lg;
			case 4:
				return Lb;
			case 5:
				return Lf;
			case 6:
				return Lh;
			case 7:
				return Ld;
			default:
				return La; //anything
			}
		}
	}
}

bool compare(LOCATION centre, LOCATION x, LOCATION loc) {
	LOCATION buffer(centre.x + loc.x, centre.y + loc.y);
	if (buffer == x)
		return true;
	else
		return false;
}

inline void transform(LOCATION &buffer, LOCATION original, LOCATION transformation) {
	buffer.x = original.x + transformation.x;
	buffer.y = original.y + transformation.y;
}