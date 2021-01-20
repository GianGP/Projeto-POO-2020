#include "Pieces.h"

pawn::pawn():piece(){}

pawn::pawn(bool color, int posX, int posY, int number):piece(color, posX, posY, number){
}

int pawn::validMovement(int newPos[2], int board[][8]){
	if (white){
		if (position[1] != newPos[1] + 1){	//nao pode andar mais de uma casa por vez, mas
			//se for o primeiro movimento e as casas estiverem livres, pode andar 2
			if (position[1] == 6 && position[1] == newPos[1] + 2 && position[0] == newPos[0] && board[newPos[1]+1][newPos[0]] == 0 && board[newPos[1]][newPos[0]] == 0 ){ 
				return 1;
			}
			return 0;
		}
			
		if (position[0] != newPos[0]){		//nao pode andar na horizontal mas
			//se tiver uma peca na diagonal a frente, pode comer
			if (position[0] == newPos[0] + 1 || position[0] == newPos[0] - 1){
				if ( board[newPos[1]][newPos[0]] >= 71 && position[1] == newPos[1] + 1){
					return 1;
				}
			}
			return 0;
		}
			
		if (position[1] == newPos[1] + 1 && board[newPos[1]][newPos[0]] != 0){	//nao pode andar se tiver uma peca na frente
			return 0;
		}
	}
	else{
		if (position[1] != newPos[1] - 1){	//nao pode andar mais de uma casa por vez, mas
			//se for o primeiro movimento e as casas estiverem livres, pode andar 2
			if (position[1] == 1 && position[1] == newPos[1] - 2 && position[0] == newPos[0] && board[newPos[1]-1][newPos[0]] == 0 && board[newPos[1]][newPos[0]] == 0 ){ 
				return 1;
			}
			return 0;
		}
			
		if (position[0] != newPos[0]){		//nao pode andar na horizontal mas
			//se tiver uma peca na diagonal a frente, pode comer
			if (position[0] == newPos[0] + 1 || position[0] == newPos[0] - 1){
				if ( board[newPos[1]][newPos[0]] > 0 && board[newPos[1]][newPos[0]] < 71 && position[1] == newPos[1] - 1){
					return 1;
				}
			}
			return 0;
		}
			
		if (position[1] == newPos[1] - 1 && board[newPos[1]][newPos[0]] != 0){	//nao pode andar se tiver uma peca na frente
			return 0;
		}
	}
	return 1;
}
