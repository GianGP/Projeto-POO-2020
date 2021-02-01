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
	
	//Variáveis para controlar o movimento especial enPassant
	enPassantID = 0;
	enPassant[0] = 0;
	enPassant[1] = 0;
	
	//Variável que controla as casas que são pintadas em destaque quando um cheque é realizado. Pinta a casa do rei e a casa da peça que esta atacando o rei.
	printCheck = false;
	
	//Posição da peça escolhida (oldPos) e posição do movimento (newPos)
	oldPos[0] = 0;
	oldPos[1] = 0;
	newPos[0] = 0;
	newPos[1] = 0;
	
	
	//Posição do rei quando ele esta em cheque (linha 0) e da peça que esta atacando/atacaria o rei (linha 1)
	checkPos[0][0] = 0;
	checkPos[0][1] = 0;
	checkPos[1][0] = 0;
	checkPos[1][1] = 0;
	
	//Zera todos os valores do board para evitar iniciar a matriz com os valores na memória
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board[i][j] = 0;
		}
	}
	//Passa o endereço de todos os objetos para o ponteiro
	for(int i = 0; i < 8; i++){
		Wpieces[0][i] = &WP[i];
		Bpieces[0][i] = &BP[i];
	}
	for (int i = 0; i < 2; i++){
		Wpieces[1][7*i] = &WR[i];
		Wpieces[1][5*i + 1] = &WKN[i];
		Wpieces[1][3*i + 2] = &WB[i];
		
		Bpieces[1][7*i] = &BR[i];
		Bpieces[1][5*i + 1] = &BKN[i];
		Bpieces[1][3*i + 2] = &BB[i];
	}
	
	//Wpieces[1][3] = &WQ[0];
	Wpieces[1][4] = &WKG;
	
	//Bpieces[1][3] = &BQ[0];
	Bpieces[1][4] = &BKG;
	
	//Atribui valore para todos os objetos referente as peças. Também atualiza o valor na matriz board conforme as peças são criadas
	for(int i = 0; i < 8; i++){
		Wpieces[0][i]->setData(true, i, 6, 11+i);
		Bpieces[0][i]->setData(false, i, 1, 71+i);
		board[6][i] = 11+i;
		board[1][i] = 71+i; 
	}
	
	for(int i = 0; i < 2; i++){
			Wpieces[1][7*i]->setData(true, 7*i, 7, 21+i);
			Wpieces[1][5*i+1]->setData(true, 5*i + 1, 7, 31+i);
			Wpieces[1][3*i+2]->setData(true, 3*i + 2, 7, 41+i);
			
			Bpieces[1][7*i]->setData(false, 7*i, 0, 81+i);
			Bpieces[1][5*i+1]->setData(false, 5*i + 1, 0, 91+i);
			Bpieces[1][3*i+2]->setData(false, 3*i + 2, 0, 101+i);
			
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
	
	Wpieces[1][4]->setData(true, 4, 7, 61);
	Bpieces[1][4]->setData(false, 4, 0, 121);
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
	int enPassantPos[2] = {0,0};
	
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
			if(enPassantID != 0 && oldPos[1] == 3){
				enPassantPos[0] = enPassant[0];
				enPassantPos[1] = enPassant[1] - 1;
				Bpieces[0][enPassantID%10 - 1]->move(enPassantPos, board);
			}
			if(Wpieces[0][piecePos-1]->validMovement(newPos, board)){
				Wpieces[0][piecePos-1]->getPos(tempPos); // CH01 OK
				Wpieces[0][piecePos-1]->move(newPos,board);
				//CH01
				if (WKG.check(board,checkPos)){
					Wpieces[0][piecePos-1]->move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					if(enPassantID != 0){
						Bpieces[0][enPassantID%10 - 1]->move(enPassant, board);
					}
					return 2;
				}
				else{
					// Promoção peão para rainha
					if(enPassantID == board[enPassantPos[1]][enPassantPos[0]] && enPassantID != 0){
						Bpieces[0][enPassantID%10 -1]->move(enPassant,board);
					}
					
					if (newPos[1] == 0){				
						WQ[piecePos].bishop::setData(true, newPos[0], newPos[1], 50 + piecePos + 1);
						board[newPos[1]][newPos[0]] = 50 + piecePos + 1;
					}else if(newPos[1] == 4 && oldPos[1] == 6){
						enPassantID = board[newPos[1]][newPos[0]];
						enPassant[0] = newPos[0];
						enPassant[1] = newPos[1];
					}
					
					return 0;
				}
				//CH01 OK
			}
			break;
		
		//TORRE BRANCA
		case 2:
			if(Wpieces[1][7*(piecePos-1)]->validMovement(newPos,board)){
				Wpieces[1][7*(piecePos-1)]->getPos(tempPos);
				Wpieces[1][7*(piecePos-1)]->move(newPos,board);
				if (WKG.check(board,checkPos)){
					Wpieces[1][7*(piecePos-1)]->move(tempPos,board);
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
			if(Wpieces[1][(piecePos-1)*5+1]->validMovement(newPos,board)){
				Wpieces[1][(piecePos-1)*5+1]->getPos(tempPos);
				Wpieces[1][(piecePos-1)*5+1]->move(newPos,board);
				if (WKG.check(board,checkPos)){
					Wpieces[1][(piecePos-1)*5+1]->move(tempPos,board);
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
			if(Wpieces[1][(piecePos-1)*3+2]->validMovement(newPos,board)){
				Wpieces[1][(piecePos-1)*3+2]->getPos(tempPos);
				Wpieces[1][(piecePos-1)*3+2]->move(newPos,board);
				if (WKG.check(board,checkPos)){
					Wpieces[1][(piecePos-1)*3+2]->move(tempPos,board);
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
			Wpieces[1][4]->getPos(tempPos);
			if(WKG.castling && WR[1].castling && !WKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]-1;
				if(Wpieces[1][4]->validMovement(newPos,board)==2 && Wpieces[1][7]->validMovement(oldPos,board) == 1){
					Wpieces[1][4]->move(newPos,board);
					if (WKG.check(board,checkPos)){
						Wpieces[1][4]->move(tempPos,board);
						return 2;
					}
					else{
						WKG.castling = false;	
						Wpieces[1][7]->move(castlingPos,board);
						WR[1].castling = false;
						return 0;
					}	
				}
			}
			if(WKG.castling && WR[0].castling && !WKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]+1;
				if(Wpieces[1][4]->validMovement(newPos,board) == -2 && Wpieces[1][0]->validMovement(oldPos,board) == 1){
					Wpieces[1][4]->move(newPos,board);
					if (WKG.check(board,checkPos)){
						Wpieces[1][4]->move(tempPos,board);
						return 2;
					}
					else{
						WKG.castling = false;	
						Wpieces[1][0]->move(castlingPos,board);
						WR[0].castling = false;
						return 0;
					}
				}
			}
			if(Wpieces[1][4]->validMovement(newPos,board) == 1){
				Wpieces[1][4]->move(newPos,board);
				if (WKG.check(board,checkPos)){
					Wpieces[1][4]->move(tempPos,board);
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
			if(enPassantID != 0 && oldPos[1] == 4){
				enPassantPos[0] = enPassant[0];
				enPassantPos[1] = enPassant[1] + 1;
				Wpieces[0][enPassantID%10 - 1]->move(enPassantPos, board);
			}
			if(Bpieces[0][piecePos-1]->validMovement(newPos, board)){
				Bpieces[0][piecePos-1]->getPos(tempPos); // CH01 OK
				Bpieces[0][piecePos-1]->move(newPos,board);
				//CH01
				if (BKG.check(board,checkPos)){
					Bpieces[0][piecePos-1]->move(tempPos,board);
					board[newPos[1]][newPos[0]] = tempID;
					if(enPassantID != 0){
						Wpieces[0][enPassantID%10 - 1]->move(enPassant, board);
					}
					return 2;
				}
				else{
					// Promoção peão para rainha
					if(enPassantID == board[enPassantPos[1]][enPassantPos[0]] && enPassantID != 0){
						Wpieces[0][enPassantID%10 -1]->move(enPassant,board);
					}
					if (newPos[1] == 7){				
						BQ[piecePos].bishop::setData(false, newPos[0], newPos[1], 110 + piecePos + 1);
						board[newPos[1]][newPos[0]] = 110 + piecePos + 1;
					}else if(newPos[1] == 3 && oldPos[1] == 1){
						enPassantID = board[newPos[1]][newPos[0]];
						enPassant[0] = newPos[0];
						enPassant[1] = newPos[1];
					}
					return 0;
				}
				//CH01 OK
			}
			break;
			
		//TORRE PRETA
		case 8:
			if(Bpieces[1][7*(piecePos-1)]->validMovement(newPos,board)){
				Bpieces[1][7*(piecePos-1)]->getPos(tempPos);
				Bpieces[1][7*(piecePos-1)]->move(newPos,board);
				if (BKG.check(board,checkPos)){
					Bpieces[1][7*(piecePos-1)]->move(tempPos,board);
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
			if(Bpieces[1][(piecePos-1)*5+1]->validMovement(newPos,board)){
				Bpieces[1][(piecePos-1)*5+1]->getPos(tempPos);
				Bpieces[1][(piecePos-1)*5+1]->move(newPos,board);
				if (BKG.check(board,checkPos)){
					Bpieces[1][(piecePos-1)*5+1]->move(tempPos,board);
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
			if(Bpieces[1][(piecePos-1)*3+2]->validMovement(newPos,board)){
				Bpieces[1][(piecePos-1)*3+2]->getPos(tempPos);
				Bpieces[1][(piecePos-1)*3+2]->move(newPos,board);
				if (BKG.check(board,checkPos)){
					Bpieces[1][(piecePos-1)*3+2]->move(tempPos,board);
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
			Bpieces[1][4]->getPos(tempPos);
			if(BKG.castling && BR[1].castling && !BKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]-1;
				if(Bpieces[1][4]->validMovement(newPos,board)==2 && Bpieces[1][7]->validMovement(oldPos,board) == 1){
					Bpieces[1][4]->move(newPos,board);
					if (BKG.check(board,checkPos)){
						Bpieces[1][4]->move(tempPos,board);
						return 2;
					}
					else{
						BKG.castling = false;	
						Bpieces[1][7]->move(castlingPos,board);
						BR[1].castling = false;
						return 0;
					}	
				}
			}
			if(BKG.castling && BR[0].castling && !BKG.check(board,checkPos)){
				castlingPos[0] = newPos[0]+1;
				if(Bpieces[1][4]->validMovement(newPos,board) == -2 && Bpieces[1][0]->validMovement(oldPos,board) == 1){
					Bpieces[1][4]->move(newPos,board);
					if (BKG.check(board,checkPos)){
						Bpieces[1][4]->move(tempPos,board);
						return 2;
					}
					else{
						BKG.castling = false;	
						Bpieces[1][0]->move(castlingPos,board);
						BR[0].castling = false;
						return 0;
					}
				}
			}
			if(Bpieces[1][4]->validMovement(newPos,board) == 1){
				Bpieces[1][4]->move(newPos,board);
				if (BKG.check(board,checkPos)){
					Bpieces[1][4]->move(tempPos,board);
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

	if(enPassantID == board[enPassantPos[1]][enPassantPos[0]] && enPassantID != 0){
		if(enPassantID > 71){
			Bpieces[0][enPassantID%10 -1]->move(enPassant,board);	
		}else{
			Wpieces[0][enPassantID%10 -1]->move(enPassant,board);
		}
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
			if(nextMove){
				if(enPassantID < 71){
					enPassantID = 0;
				}
			}else{
				if(enPassantID > 61){
					enPassantID = 0;
				}
			}
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

void Game::operator --(){
	printOld = false;
	printNew = false;
	printCheck = false;
}
