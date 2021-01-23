#include "Pieces.h"
#include <stdlib.h>

king::king():piece(){
	castling = true;
}

king::king(bool color, int posX, int posY, int number):piece(color, posX, posY, number){
}

int king::validMovement(int newPos[2], int board[][8]){
	int movement_x = abs(newPos[0] - position[0]);
	int movement_y = abs(newPos[1] - position[1]);
	
	
	if (white){
		
		if((movement_x == 2 && movement_y == 0)){
				return (newPos[0] - position[0]);
			}
		
		if ((movement_x == 1 && movement_y == 0) || (movement_x == 0 && movement_y == 1) || (movement_x == 1 && movement_y == 1)){
			return 1;
		}
	}
	else{
		
		if((movement_x == 2 && movement_y == 0)){
				return (newPos[0] - position[0]);
			}
		
		
		if ((movement_x == 1 && movement_y == 0) || (movement_x == 0 && movement_y == 1) || (movement_x == 1 && movement_y == 1)){
			return 1;
		}
	}
	return 0;
}

void king::setData(bool inputCastling){
	castling = inputCastling;
	return;
}

//CH01

int king::check(int board[][8]){
	int kingY = position[1], kingX = position[0];
	
	if (white){
		//CAVALO
		if (kingY+2 <=7 && kingX+1 <=7){
			if (board[kingY+2][kingX+1]/10 == 9){
				return 1;
			}
		}
		
		if (kingY+2 <=7 && kingX-1 >=0){
			if (board[kingY+2][kingX-1]/10 == 9){
				return 1;
			}
		}
		
		if (kingY+1 <=7 && kingX+2 <=7){	
			if (board[kingY+1][kingX+2]/10 == 9){
				return 1;
			}
		}
		
		if (kingY+1 <=7 && kingX-2 >=0){	
			if (board[kingY+1][kingX-2]/10 == 9){
				return 1;
			}
		}	
		
		if (kingY-1 >=0 && kingX+2 <=7){	
			if (board[kingY-1][kingX+2]/10 == 9){
				return 1;
			}
		}
		
		if (kingY-1 >=0 && kingX-2 >=0){	
			if (board[kingY-1][kingX-2]/10 == 9){
				return 1;
			}
		}	
		
		if (kingY-2 >=0 && kingX+1 <=7){	
			if (board[kingY-2][kingX+1]/10 == 9){
				return 1;
			}
		}
	
		if (kingY-2 >=0 && kingX-1 >=0){	
			if (board[kingY-2][kingX-1]/10 == 9){
				return 1;
			}
		}
		
		//PEAO
		if (kingY-1 >=0){
			if (kingX-1 >=0){
				if (board[kingY-1][kingX-1]/10 == 7){
					return 1;
				}
			}
			if (kingX+1 <=7){
				if (board[kingY-1][kingX+1]/10 == 7){
					return 1;
				}
			}
		}
		
		//TORRE (E DAMA)
		for(int i=1, stop=1; stop==1 && kingY+i<=7; i++){ //baixo
			if (board[kingY+i][kingX]/10 == 11 || board[kingY+i][kingX]/10 == 8){
				return 1;
			}
			if (board[kingY+i][kingX]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1,stop=1; stop==1 && kingY-i>=0; i++){ //cima
			if (board[kingY-i][kingX]/10 == 11 || board[kingY-i][kingX]/10 == 8){
				return 1;
			}
			if (board[kingY-i][kingX]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingX+i<=7; i++){ // direita
			if (board[kingY][kingX+i]/10 == 11 || board[kingY][kingX+i]/10 == 8){
				return 1;
			}
			if (board[kingY][kingX+i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1,stop=1; stop==1 && kingX-i>=0; i++){ //esquerda
			if (board[kingY][kingX-i]/10 == 11 || board[kingY][kingX-i]/10 == 8){
				return 1;
			}
			if (board[kingY][kingX-i]/10 != 0){
				stop=0;
			}
		}
		
		//BISPO (E DAMA)
		for(int i=1, stop=1; stop==1 && kingY+i<=7 && kingX+i<=7; i++){ //sudeste
			if (board[kingY+i][kingX+i]/10 == 11 || board[kingY+i][kingX+i]/10 == 10){
				return 1;
			}
			if (board[kingY+i][kingX+i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingY+i<=7 && kingX-i>=0; i++){ //sudoeste
			if (board[kingY+i][kingX-i]/10 == 11 || board[kingY+i][kingX-i]/10 == 10){
				return 1;
			}
			if (board[kingY+i][kingX-i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingY-i>=0 && kingX+i<=7; i++){ //nordeste
			if (board[kingY-i][kingX+i]/10 == 11 || board[kingY-i][kingX+i]/10 == 10){
				return 1;
			}
			if (board[kingY-i][kingX+i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingY-i>=0 && kingX-i>=0; i++){ //noroeste
			if (board[kingY-i][kingX-i]/10 == 11 || board[kingY-i][kingX-i]/10 == 10){
				return 1;
			}
			if (board[kingY-i][kingX-i]/10 != 0){
				stop=0;
			}
		}
	
		//REI
		if (board[kingY+1][kingX+1] == 121){ // sudeste
			return 1;
		}
		if (board[kingY+1][kingX] == 121){   // sul
			return 1;
		}
		if (board[kingY+1][kingX-1] == 121){ // sudoeste
			return 1;
		}
		if (board[kingY][kingX-1] == 121){   // oeste
			return 1;
		}
		if (board[kingY-1][kingX-1] == 121){ // noroeste
			return 1;
		}
		if (board[kingY-1][kingX] == 121){   // norte
			return 1;
		}
		if (board[kingY-1][kingX+1] == 121){ // nordeste
			return 1;
		}
		if (board[kingY][kingX+1] == 121){   // leste
			return 1;
		}
	}
	else{	
		//CAVALO		
		if (kingY+2 <=7 && kingX+1 <=7){
			if (board[kingY+2][kingX+1]/10 == 3){
				return 1;
			}
		}
		
		if (kingY+2 <=7 && kingX-1 >=0){
			if (board[kingY+2][kingX-1]/10 == 3){
				return 1;
			}
		}
		
		if (kingY+1 <=7 && kingX+2 <=7){	
			if (board[kingY+1][kingX+2]/10 == 3){
				return 1;
			}
		}
		
		if (kingY+1 <=7 && kingX-2 >=0){	
			if (board[kingY+1][kingX-2]/10 == 3){
				return 1;
			}
		}	
		
		if (kingY-1 >=0 && kingX+2 <=7){	
			if (board[kingY-1][kingX+2]/10 == 3){
				return 1;
			}
		}
		
		if (kingY-1 >=0 && kingX-2 >=0){	
			if (board[kingY-1][kingX-2]/10 == 3){
				return 1;
			}
		}	
		
		if (kingY-2 >=0 && kingX+1 <=7){	
			if (board[kingY-2][kingX+1]/10 == 3){
				return 1;
			}
		}
	
		if (kingY-2 >=0 && kingX-1 >=0){	
			if (board[kingY-2][kingX-1]/10 == 3){
				return 1;
			}
		}
		
		//PEAO
		if (kingY+1 <=7){
			if (kingX-1 >=0){
				if (board[kingY+1][kingX-1]/10 == 1){
					return 1;
				}
			}
			if (kingX+1 <=7){
				if (board[kingY+1][kingX+1]/10 == 1){
					return 1;
				}
			}
		}
		
		//TORRE (E DAMA)
		for(int i=1, stop=1; stop==1 && kingY+i<=7; i++){ //baixo
			if (board[kingY+i][kingX]/10 == 5 || board[kingY+i][kingX]/10 == 2){
				return 1;
			}
			if (board[kingY+i][kingX]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1,stop=1; stop==1 && kingY-i>=0; i++){ //cima
			if (board[kingY-i][kingX]/10 == 5 || board[kingY-i][kingX]/10 == 2){
				return 1;
			}
			if (board[kingY-i][kingX]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingX+i<=7; i++){ // direita
			if (board[kingY][kingX+i]/10 == 5 || board[kingY][kingX+i]/10 == 2){
				return 1;
			}
			if (board[kingY][kingX+i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1,stop=1; stop==1 && kingX-i>=0; i++){ //esquerda
			if (board[kingY][kingX-i]/10 == 5 || board[kingY][kingX-i]/10 == 2){
				return 1;
			}
			if (board[kingY][kingX-i]/10 != 0){
				stop=0;
			}
		}
		
		//BISPO (E DAMA)
		for(int i=1, stop=1; stop==1 && kingY+i<=7 && kingX+i<=7; i++){ //sudeste
			if (board[kingY+i][kingX+i]/10 == 5 || board[kingY+i][kingX+i]/10 == 4){
				return 1;
			}
			if (board[kingY+i][kingX+i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingY+i<=7 && kingX-i>=0; i++){ //sudoeste
			if (board[kingY+i][kingX-i]/10 == 5 || board[kingY+i][kingX-i]/10 == 4){
				return 1;
			}
			if (board[kingY+i][kingX-i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingY-i>=0 && kingX+i<=7; i++){ //nordeste
			if (board[kingY-i][kingX+i]/10 == 5 || board[kingY-i][kingX+i]/10 == 4){
				return 1;
			}
			if (board[kingY-i][kingX+i]/10 != 0){
				stop=0;
			}
		}
		
		for(int i=1, stop=1; stop==1 && kingY-i>=0 && kingX-i>=0; i++){ //noroeste
			if (board[kingY-i][kingX-i]/10 == 5 || board[kingY-i][kingX-i]/10 == 4){
				return 1;
			}
			if (board[kingY-i][kingX-i]/10 != 0){
				stop=0;
			}
		}
	
		//REI
		if (board[kingY+1][kingX+1] == 61){ // sudeste
			return 1;
		}
		if (board[kingY+1][kingX] == 61){   // sul
			return 1;
		}
		if (board[kingY+1][kingX-1] == 61){ // sudoeste
			return 1;
		}
		if (board[kingY][kingX-1] == 61){   // oeste
			return 1;
		}
		if (board[kingY-1][kingX-1] == 61){ // noroeste
			return 1;
		}
		if (board[kingY-1][kingX] == 61){   // norte
			return 1;
		}
		if (board[kingY-1][kingX+1] == 61){ // nordeste
			return 1;
		}
		if (board[kingY][kingX+1] == 61){   // leste
			return 1;
		}
	}
	return 0;
}
