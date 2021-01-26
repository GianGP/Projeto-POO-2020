#include "Game.h"
#include<iostream>

Game::Game(){
	//Variavel que controla qual cor realiza o movimento (true: brancas, false: pretas)
	nextMove = true;
	
	//Variaveis que controlam as casas que são pintadas em destaque no tabuleiro. 
	//printOld true - casa selecionada (e que contem peça fica em destaque).
	//printNew true - destaca o último movimento realizado, pintando a casa de origem do movimento e casa final.
	printOld = false;
	printNew = false;
	
	//Variável que controla as casas que são pintadas em destaque quando um cheque é realizado. Pinta a casa do rei e a casa da peça que esta atacando o rei.
	printCheck = false;
	
	oldPos[0] = 0;
	oldPos[1] = 0;
	newPos[0] = 0;
	newPos[1] = 0;
	
	checkPos[0][0] = 0;
	checkPos[0][1] = 0;
	checkPos[1][0] = 0;
	checkPos[1][1] = 0;
	
	//Atribui valore para todos os objetos referente as peças. Também atualiza o valor na matriz board conforme as peças são criadas
	for(int i = 0; i < 8; i++){
		WP[i].setData(true, i, 6, 11+i);
		BP[i].setData(false, i, 1, 71+i);
		board[6][i] = 11+i;
		board[1][i] = 71+i; 
	}
	
	for(int i = 0; i < 2; i++){
			WR[i].piece::setData(true, 7*i, 7, 21+i);
			WKN[i].setData(true, 5*i + 1, 7, 31+i);
			WB[i].setData(true, 3*i + 2, 7, 41+i);
			
			BR[i].piece::setData(false, 7*i, 0, 81+i);
			BKN[i].setData(false, 5*i + 1, 0, 91+i);
			BB[i].setData(false, 3*i + 2, 0, 101+i);
			
			board[7][7*i] = 21+i;
			board[7][5*i+1] = 31+i;
			board[7][3*i+2] = 41+i;
			
			board[0][7*i] = 81+i;
			board[0][5*i+1] = 91+i;
			board[0][3*i+2] = 101+i;; 
	}
	
	WQ[0].bishop::setData(true, 3, 7, 51);
	BQ[0].bishop::setData(false, 3, 0, 111);
	board[7][3] = 51;
	board[0][3] = 111;
	
	WKG.piece::setData(true, 4, 7, 61);
	BKG.piece::setData(false, 4, 0, 121);
	board[7][4] = 61;
	board[0][4] = 121;
}

int Game::movementValid(){
	int castlingPos[2];
	castlingPos[1] = newPos[1];
	int pieceID = board[oldPos[1]][oldPos[0]]/10;
	int piecePos = board[oldPos[1]][oldPos[0]]%10;
	//CH01
	int tempPos[2] = {0,0}; // OK
	int tempID = board[newPos[1]][newPos[0]];
	
	// Decide qual cor fara o movimento. 
	if(nextMove){
		if(board[oldPos[1]][oldPos[0]] > 61){
			return 1;
		}
	} else {
		if(board[oldPos[1]][oldPos[0]] < 71){
			return 1;
		}
	}
	
	//nao deixa comer pecas da sua cor
	if (board[newPos[1]][newPos[0]] != 0){
		if ((board[oldPos[1]][oldPos[0]] <= 61 && board[newPos[1]][newPos[0]] <=61) || (board[oldPos[1]][oldPos[0]] >= 71 && board[newPos[1]][newPos[0]] >= 71) ){
			return 1;
		}
	} 
	
	//Verifica qual foi a peça escolhida e determina se o movimento é válido ou não
	switch (pieceID){
		//PEAO BRANCO
		case 1:
			if(WP[piecePos-1].validMovement(newPos, board)){
				WP[piecePos-1].getPos(tempPos); // CH01 OK
				WP[piecePos-1].move(newPos,board);
				//CH01
				if (WKG.check(board,checkPos)){
					WP[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					// Promoção peão para rainha
					if (newPos[1] == 0){				
						WQ[piecePos].bishop::setData(true, newPos[0], newPos[1], 50 + piecePos + 1);
						board[newPos[1]][newPos[0]] = 50 + piecePos + 1;
					}
					
					return 0;
				}
				//CH01 OK
			}
			break;
		
		//TORRE BRANCA
		case 2:
			if(WR[piecePos-1].validMovement(newPos,board)){
				WR[piecePos-1].getPos(tempPos);
				WR[piecePos-1].move(newPos,board);
				if (WKG.check(board,checkPos)){
					WR[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					if(WR[piecePos-1].castling){
						WR[piecePos-1].castling = false;
					}
					return 0;
				}
			}
			break;
		
		//CAVALO BRANCO	
		case 3:
			if(WKN[piecePos-1].validMovement(newPos,board)){
				WKN[piecePos-1].getPos(tempPos);
				WKN[piecePos-1].move(newPos,board);
				if (WKG.check(board,checkPos)){
					WKN[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					return 0;
				}
			}	
			break;
			
		//BISPO BRANCO
		case 4:
			if(WB[piecePos-1].validMovement(newPos,board)){
				WB[piecePos-1].getPos(tempPos);
				WB[piecePos-1].move(newPos,board);
				if (WKG.check(board,checkPos)){
					WB[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					return 0;
				}
			}
			break;
		
		//RAINHA BRANCA
		case 5:
			WQ[piecePos-1].bishop::getPos(tempPos);
			if(WQ[piecePos-1].validMovement(newPos,board)){	
				WQ[piecePos-1].bishop::move(newPos,board);
				if (WKG.check(board,checkPos)){
					WQ[piecePos-1].bishop::move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					return 0;
				}
			}
			break;
		
		//REI BRANCO
		case 6:
			WKG.getPos(tempPos);
			if(WKG.castling && WR[1].castling && !WKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]-1;
				if(WKG.validMovement(newPos,board)==2 && WR[1].validMovement(oldPos,board) == 1){
					WKG.move(newPos,board);
					if (WKG.check(board,checkPos)){
						WKG.move(tempPos,board);
						return 2;
					}
					else{
						WKG.castling = false;	
						WR[1].move(castlingPos,board);
						WR[1].castling = false;
						return 0;
					}	
				}
			}
			if(WKG.castling && WR[0].castling && !WKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]+1;
				if(WKG.validMovement(newPos,board) == -2 && WR[0].validMovement(oldPos,board) == 1){
					WKG.move(newPos,board);
					if (WKG.check(board,checkPos)){
						WKG.move(tempPos,board);
						return 2;
					}
					else{
						WKG.castling = false;	
						WR[0].move(castlingPos,board);
						WR[0].castling = false;
						return 0;
					}
				}
			}
			if(WKG.validMovement(newPos,board) == 1){
				WKG.move(newPos,board);
				if (WKG.check(board,checkPos)){
					WKG.move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					if(WKG.castling){
						WKG.castling = false;
					}
					return 0;
				}
			}
			break;
			
		//PEAO PRETO
		case 7:
			if(BP[piecePos-1].validMovement(newPos, board)){
				BP[piecePos-1].getPos(tempPos); // CH01 OK
				BP[piecePos-1].move(newPos,board);
				//CH01
				if (BKG.check(board,checkPos)){
					BP[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					// Promoção peão para rainha
					if (newPos[1] == 0){				
						BQ[piecePos].bishop::setData(true, newPos[0], newPos[1], 110 + piecePos + 1);
						board[newPos[1]][newPos[0]] = 110 + piecePos + 1;
					}
					return 0;
				}
				//CH01 OK
			}
			break;
			
		//TORRE PRETA
		case 8:
			if(BR[piecePos-1].validMovement(newPos,board)){
				BR[piecePos-1].getPos(tempPos);
				BR[piecePos-1].move(newPos,board);
				if (BKG.check(board,checkPos)){
					BR[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					if(BR[piecePos-1].castling){
						BR[piecePos-1].castling = false;
					}
					return 0;
				}
			}
			break;
			
		//CAVALO PRETO
		case 9:
			if(BKN[piecePos-1].validMovement(newPos,board)){
				BKN[piecePos-1].getPos(tempPos);
				BKN[piecePos-1].move(newPos,board);
				if (BKG.check(board,checkPos)){
					BKN[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					return 0;
				}
			}	
			break;
			
		//BISPO PRETO
		case 10:
			if(BB[piecePos-1].validMovement(newPos,board)){
				BB[piecePos-1].getPos(tempPos);
				BB[piecePos-1].move(newPos,board);
				if (BKG.check(board,checkPos)){
					BB[piecePos-1].move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					return 0;
				}
			}
			break;				
		
		//RAINHA NEGRA
		case 11:
			BQ[piecePos-1].bishop::getPos(tempPos);
			if(BQ[piecePos-1].validMovement(newPos,board)){
				BQ[piecePos-1].bishop::move(newPos,board);
				if (BKG.check(board,checkPos)){
					BQ[piecePos-1].bishop::move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					return 0;
				}
			}
			break;		
			
		//REI PRETO
		case 12:
			BKG.getPos(tempPos);
			if(BKG.castling && BR[1].castling && !BKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]-1;
				if(BKG.validMovement(newPos,board)==2 && BR[1].validMovement(oldPos,board) == 1){
					BKG.move(newPos,board);
					if (BKG.check(board,checkPos)){
						BKG.move(tempPos,board);
						return 2;
					}
					else{
						BKG.castling = false;	
						BR[1].move(castlingPos,board);
						BR[1].castling = false;
						return 0;
					}
				}
			}
			if(BKG.castling && BR[0].castling && !BKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]+1;
				if(BKG.validMovement(newPos,board) == -2 && BR[0].validMovement(oldPos,board) == 1){
					BKG.move(newPos,board);
					if (BKG.check(board,checkPos)){
						BKG.move(tempPos,board);
						return 2;
					}
					else{
						BKG.castling = false;	
						BR[0].move(castlingPos,board);
						BR[0].castling = false;
						return 0;
					}
				}
			}
			if(BKG.validMovement(newPos,board) == 1){
				BKG.move(newPos,board);
				if (BKG.check(board,checkPos)){
					BKG.move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					return 2;
				}
				else{
					if(BKG.castling){
						BKG.castling = false;
					}
					return 0;
				}
			}
			break;	
	}

return 1; // Caso nao valide o movimento, retorna 1 para que nao execute
}

void Game::Event_Left(int x, int y, int sizeX, int sizeY){
	if(!printOld){		//se print old false
		oldPos[0] = x/sizeX;	//captura a posicao do clique
		oldPos[1] = y/sizeY;
		if(board[oldPos[1]][oldPos[0]] != 0){		//se nao for zero (casa vazia) seleciona a peca
			printOld = true;					//seta printOld para que no proximo evento de botao esquerdo não entre no mesmo escopo
			printNew = false;
		} else {
			printOld = false;					// se for uma casa vazia, não faz nada
			printNew = false;
		}		
	} else if (printOld && !printNew){			//caso uma peca esteja selecionada
		newPos[0] = x/sizeX; 	//captura a posicao de destino
		newPos[1] = y/sizeY;
		if(movementValid() == 0){
			printOld = false;
			printNew = true;
			printCheck = false;
			nextMove = nextMove^true;
		}else if (movementValid() == 2){
			printOld = false;
			printNew = false;
			printCheck = true;
		}else{
			printOld = false;
			printNew = false;
			printCheck = false;
		}
	}
}

void Game::Event_Right(){
	printOld = false;
	printNew = false;
	printCheck = false;
}
