#include "Pieces.h"

queen::queen(bool color1, bool state1, int posX1, int posY1, int number1, bool color2, bool state2, int posX2, int posY2, int number2) :
	bishop(color1, state1, posX1, posY1, number1), rook(color2, state2, posX2, posY2, number2) {}

int queen::validMovement(int oldPos[2], int newPos[2], int board[][8])
{
	int bishopMove, rookMove;
	
	bishopMove = bishop::validMovement(oldPos, newPos, board);
	rookMove = rook::validMovement(oldPos, newPos, board);
	
	if(bishopMove || rookMove) return 1;
	return 0;
}
