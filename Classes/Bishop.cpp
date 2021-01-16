#include "Pieces.h"
#include <stdlib.h>

bishop::bishop(bool color, bool state, int posX, int posY, int number) : piece(color, state, posX, posY, number) {}

int bishop::validMovement(int oldPos[2], int newPos[2], int board[][8])
{
	//checando se esta dentro da diagonal
	if(abs(newPos[0] - oldPos[0]) != abs(newPos[1] - oldPos[1])) return 0;
	
	//checando se o caminho esta livre
	if(newPos[0] < oldPos[0] && newPos[1] < oldPos[1])				//esquerda e acima
	{
		for(int i = 1; i < oldPos[0] - newPos[0]; i++)
		{
			if(board[oldPos[1] - i][oldPos[0] - i] != 0) return 0;
		}
		return 1;
	}
	if(newPos[0] < oldPos[0] && newPos[1] > oldPos[1])				//esquerda e abaixo
	{
		for(int i = 1; i < oldPos[0] - newPos[0]; i++)
		{
			if(board[oldPos[1] + i][oldPos[0] - i] != 0) return 0;
		}
		return 1;
	}
	if(newPos[0] > oldPos[0] && newPos[1] < oldPos[1])				// direita e acima
	{
		for(int i = 1; i < newPos[0] - oldPos[0]; i++)
		{
			if(board[oldPos[1] - i][oldPos[0] + i] != 0) return 0;
		}
		return 1;
	}
	else															//direita e abaixo
	{
		for(int i = 1; i < newPos[0] - oldPos[0]; i++)
		{
			if(board[oldPos[1] + i][oldPos[0] + i] != 0) return 0;
		}
		return 1;
	}
	
	return 0;
}
