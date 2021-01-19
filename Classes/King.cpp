#include "Pieces.h"
#include <stdlib.h>

king::king():piece(){
}

king::king(bool color, int posX, int posY, int number):piece(color, posX, posY, number){
}

int king::validMovement(int newPos[2], int board[][8]){
	int movement_x = abs(newPos[0] - position[0]);
	int movement_y = abs(newPos[1] - position[1]);
	
	
	if (white){
		if ((movement_x == 1 && movement_y == 0) || (movement_x == 0 && movement_y == 1) || (movement_x == 1 && movement_y == 1)){
			return 1;
		}
	}
	else{
		if ((movement_x == 1 && movement_y == 0) || (movement_x == 0 && movement_y == 1) || (movement_x == 1 && movement_y == 1)){
			return 1;
		}
	}
	return 0;
}
