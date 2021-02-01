#include "Pieces.h"
queen::queen():bishop(),rook(){
}

queen::queen(bool color, int posX, int posY, int number){
		bishop::setData(color, posX, posY, number),	rook::setData(color, posX, posY , number);
	}

int queen::validMovement(int newPos[2], int board[][8])
{
	updateValue();
	int bishopMove, rookMove;
	
	rookMove = rook::validMovement(newPos, board);
	bishopMove = bishop::validMovement(newPos, board);
	
	if(bishopMove || rookMove) {
		bishop::move(newPos, board);
		rook::move(newPos, board);
		return 1;	
	}
	return 0;
}

void queen::updateValue(){
	rook::position[1] = bishop::position[1];
    rook::position[0] = bishop::position[0];
}
