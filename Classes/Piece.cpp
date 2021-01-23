#include <iostream>
#include "Pieces.h"

piece::piece(){
	white = true;
	position[0] = 0;
	position[1] = 0;
	ID = 0;
}

piece::piece(bool color, int posX, int posY, int number)
{
	white = color;
	position[1] = posX;
	position[0] = posY;
	ID = number;
}

void piece::move(int newPos[2], int board [8][8])
{
	board[position[1]][position[0]] = 0;
	board[newPos[1]][newPos[0]] = ID;
	position[0] = newPos[0];
	position[1] = newPos[1];
}

void piece::setData(bool color, int posX, int posY, int number)
{
	white = color;
	position[0] = posX;
	position[1] = posY;
	ID = number;
}
//CH01
void piece::getPos(int tempPos[2]){ // OK
	tempPos[0] = position[0];
	tempPos[1] = position[1];
	return;
}
