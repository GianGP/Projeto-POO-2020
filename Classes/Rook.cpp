#include "Pieces.h"

rook::rook(bool color, bool state, int posX, int posY, int number) : piece(color, state, posX, posY, number) {}

int rook::validMovement(int oldPos[2], int newPos[2], int board[][8])
{
	//checando se esta na mesma coluna ou na mesma linha
	if(newPos[0] != oldPos[0] && newPos[1] != oldPos[1]) return 0;
	
	//checando se o caminho esta livre
	if(newPos[0] < oldPos[0])								//esquerda
	{
		for(int i = 1; i < oldPos[0] - newPos[0]; i++)
		{
			if(board[oldPos[1]][oldPos[0] - i] != 0) return 0;
		}
		return 1;
	}
	if(newPos[0] > oldPos[0])								//direita
	{
		for(int i = 1; i < newPos[0] - oldPos[0]; i++)
		{
			if(board[oldPos[1]][oldPos[0] + i] != 0) return 0;
		}
		return 1;
	}
	if(newPos[1] < oldPos[1])								//acima
	{
		for(int i = 1; i < oldPos[1] - newPos[1]; i++)
		{
			if(board[oldPos[1] - i][oldPos[0]] != 0) return 0;
		}
		return 1;
	}
	else													//abaixo
	{
		for(int i = 1; i < newPos[1] - oldPos[1]; i++)
		{
			if(board[oldPos[1] + i][oldPos[0]] != 0) return 0;
		}
		return 1;
	}
}
