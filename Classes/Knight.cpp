#include "Pieces.h"
#include <stdlib.h>

knight::knight():piece(){
}

knight::knight(bool color, int posX, int posY, int number):piece(color, posX, posY, number){
}

int knight::validMovement(int newPos[2], int board[][8]){
	int movement_x = abs(newPos[0] - position[0]);
	int movement_y = abs(newPos[1] - position[1]);	

	if((movement_x == 1 && movement_y == 2) || (movement_x == 2 && movement_y == 1)) //Movimento em 'L' 
	{
	    return 1;
	} else {
		return 0;	
	}
}
