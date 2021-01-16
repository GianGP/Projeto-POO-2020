#include "Interface.h"
#include "Pieces.h"

bool nextMove = true; // True se o próximo movimento for das brancas, false se for das negras

//PEAO BRANCO
pawn WP1(true, true, 0, 6, 11);
pawn WP2(true, true, 1, 6, 12);
pawn WP3(true, true, 2, 6, 13);
pawn WP4(true, true, 3, 6, 14);
pawn WP5(true, true, 4, 6, 15);
pawn WP6(true, true, 5, 6, 16);
pawn WP7(true, true, 6, 6, 17);
pawn WP8(true, true, 7, 6, 18);

//TORRE BRANCA
rook WR1(true, true, 0, 7, 21);
rook WR2(true, true, 7, 7, 22);

//CAVALO BRANCO
knight WKN1(true, true, 1, 7, 31);
knight WKN2(true, true, 6, 7, 32);

//BISPO BRANCO
bishop WB1(true, true, 2, 7, 41);
bishop WB2(true, true, 5, 7, 42);

//DAMA BRANCA
queen WQ(true, true, 3, 7, 51, true, true, 3, 7, 51);

//REI BRANCO
king WKG(true, true, 4, 7, 61);

//PEAO PRETO
pawn BP1(false, true, 0, 1, 71);
pawn BP2(false, true, 1, 1, 72);
pawn BP3(false, true, 2, 1, 73);
pawn BP4(false, true, 3, 1, 74);
pawn BP5(false, true, 4, 1, 75);
pawn BP6(false, true, 5, 1, 76);
pawn BP7(false, true, 6, 1, 77);
pawn BP8(false, true, 7, 1, 78);

//TORRE PRENTA
rook BR1(false, true, 0, 0, 81);
rook BR2(false, true, 7, 0, 82);

//CAVALO PRETO
knight BKN1(false, true, 1, 0, 91);
knight BKN2(false, true, 6, 0, 92);

//BISPO PRETO
bishop BB1(false, true, 2, 0, 101);
bishop BB2(false, true, 5, 0, 102);

//DAMA PRETA
queen BQ(false, true, 3, 0, 111, false, true, 3, 0, 111);

//REI PRETO
king BKG(false, true, 4, 0, 121);

int movementValid(int oldPos[2], int newPos[2], int board[8][8]){

	//nao deixa comer pecas da sua cor
	if (board[newPos[1]][newPos[0]] != 0){
		if ((board[oldPos[1]][oldPos[0]] <= 61 && board[newPos[1]][newPos[0]] <=61) || (board[oldPos[1]][oldPos[0]] >= 71 && board[newPos[1]][newPos[0]] >= 71) ){
			return 1;
		}
	} 
	
	if(nextMove){
		if(board[oldPos[1]][oldPos[0]] > 61){
			return 1;
		}
	} else {
		if(board[oldPos[1]][oldPos[0]] < 71){
			return 1;
		}
	}
	
	switch (board[oldPos[1]][oldPos[0]]){				
		//PEAO BRANCO
		case 11:
			if (WP1.validMovement(oldPos, newPos, board)){
					WP1.move(newPos, board);
					return 0;
			}
			break;
		case 12:
			if (WP2.validMovement(oldPos, newPos, board)){
					WP2.move(newPos, board);
					return 0;
			}
			break;
		case 13:
			if (WP3.validMovement(oldPos, newPos, board)){
					WP3.move(newPos, board);
					return 0;
			}
			break;
		case 14:
			if (WP4.validMovement(oldPos, newPos, board)){
					WP4.move(newPos, board);
					return 0;
			}
			break;
		case 15:
			if (WP5.validMovement(oldPos, newPos, board)){
					WP5.move(newPos, board);
					return 0;
			}
			break;
		case 16:
			if (WP6.validMovement(oldPos, newPos, board)){
					WP6.move(newPos, board);
					return 0;
			}
			break;
		case 17:
			if (WP7.validMovement(oldPos, newPos, board)){
					WP7.move(newPos, board);
					return 0;
			}
			break;
		case 18:
			if (WP8.validMovement(oldPos, newPos, board)){
					WP8.move(newPos, board);
					return 0;
			}
			break;
		
		//TORRE BRANCA
		case 21:
			if(WR1.validMovement(oldPos,newPos,board)){
				WR1.move(newPos,board);
				return 0;
			}
			break;
			
		case 22:
			if(WR2.validMovement(oldPos,newPos,board)){
				WR2.move(newPos,board);
				return 0;
			}
			break;			
			
		//CAVALO BRANCO	
		case 31:
			if(WKN1.validMovement(oldPos,newPos,board)){
				WKN1.move(newPos, board);
				return 0; 
			}
			break;
		
		case 32:
			if(WKN2.validMovement(oldPos,newPos,board)){
				WKN2.move(newPos,board);
				return 0;
			}
			break;
			
		//BISPO BRANCO
		case 41:
			if(WB1.validMovement(oldPos,newPos,board)){
				WB1.move(newPos, board);
				return 0;
			}
			break;
			
		case 42:
			if(WB2.validMovement(oldPos,newPos,board)){
				WB2.move(newPos,board);
				return 0;
			}
			break;
		
		//RAINHA BRANCA
		case 51:	
			if(WQ.validMovement(oldPos,newPos,board)){
				WQ.bishop::move(newPos,board);
				return 0;
			}
			break;
		
		//REI BRANCO	
		case 61:
			if(WKG.validMovement(oldPos,newPos,board)){
				WKG.move(newPos, board);
				return 0;
			}
			break;
			
		//PEAO PRETO
		case 71:
			if (BP1.validMovement(oldPos, newPos, board)){
				BP1.move(newPos, board);
				return 0;
			}
			break;
		case 72:
			if (BP2.validMovement(oldPos, newPos, board)){
				BP2.move(newPos, board);
				return 0;
			}
			break;
		case 73:
			if (BP3.validMovement(oldPos, newPos, board)){
				BP3.move(newPos, board);
				return 0;
			}
			break;
		case 74:
			if (BP4.validMovement(oldPos, newPos, board)){
				BP4.move(newPos, board);
				return 0;
			}
			break;
		case 75:
			if (BP5.validMovement(oldPos, newPos, board)){
				BP5.move(newPos, board);
				return 0;
			}
			break;
		case 76:
			if (BP6.validMovement(oldPos, newPos, board)){
				BP6.move(newPos, board);
				return 0;
			}
			break;
		case 77:
			if (BP7.validMovement(oldPos, newPos, board)){
				BP7.move(newPos, board);
				return 0;
			}
			break;
		case 78:
			if (BP8.validMovement(oldPos, newPos, board)){
				BP8.move(newPos, board);
				return 0;
			}
			break;
			
		//TORRE PRETA
		case 81:
			if(BR1.validMovement(oldPos,newPos,board)){
				BR1.move(newPos,board);
				return 0;
			}
			break;
			
		case 82:
			if(BR2.validMovement(oldPos,newPos,board)){
				BR2.move(newPos,board);
				return 0;
			}
			break;				
			
		//CAVALO PRETO	
		case 91:
			if(BKN1.validMovement(oldPos,newPos,board)){
				BKN1.move(newPos, board);
				return 0; 
			}
			break;
		
		case 92:
			if(BKN2.validMovement(oldPos,newPos,board)){
				BKN2.move(newPos,board);
				return 0;
			}
			break;	
			
		//BISPO PRETO
		case 101:
			if(BB1.validMovement(oldPos,newPos,board)){
				BB1.move(newPos, board);
				return 0;
			}
			break;
			
		case 102:
			if(BB2.validMovement(oldPos,newPos,board)){
				BB2.move(newPos,board);
				return 0;
			}
			break;
			
		
		//RAINHA PRETA
		case 111:	
			if(BQ.validMovement(oldPos,newPos,board)){
				BQ.bishop::move(newPos,board);
				return 0;
			}
			break;
			
		//REI PRETO
		case 121:
			if(BKG.validMovement(oldPos,newPos,board)){
				BKG.move(newPos, board);
				return 0;
			}
			break;	
	}

return 1; // Caso nao valide o movimento, retorna 0 para que nao execute
}

Interface::interface(){
	printOld = false;
	printNew = false;
	pieceSelected = 0;
	oldPos[0] = 0;
	oldPos[1] = 0;
	newPos[0] = 0;
	newPos[1] = 0;
}

void Interface::Event_Left(int x, int y, int board[][8]){
	if(!printOld){		//se print old false
		oldPos[0] = x/100;	//captura a posicao do clique
		oldPos[1] = y/100;
		if(board[oldPos[1]][oldPos[0]] != 0){		//se nao for zero (casa vazia) seleciona a peca
			pieceSelected = board[oldPos[1]][oldPos[0]];
			printOld = true;					//seta printOld para que no proximo evento de botao esquerdo não entre no mesmo escopo
			printNew = false;
		} else {
			printOld = false;					// se for uma casa vazia, não faz nada
			printNew = false;
		}		
	} else if (printOld && !printNew){			//caso uma peca esteja selecionada
		newPos[0] = x/100; 	//captura a posicao de destino
		newPos[1] = y/100;
		if(movementValid(oldPos, newPos, board) == 0){
			printOld = false;
			printNew = true;
			nextMove = nextMove^true;
		}else{
			printOld = false;
			printNew = false;
		}
	}
}

void Interface::Event_Right(){
	printOld = false;
	printNew = false;
}

