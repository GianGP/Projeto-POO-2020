#include "Pieces.h"

class Game{
	private:
		//Define de qual cor � o pr�ximo movimento (brancas - true, negras - false)
		bool nextMove;	
		int enPassantID;
		int enPassant[2];
		
		//Pe�as brancas
		pawn WP[8]; 
		rook WR[2];
		knight WKN[2];
		bishop WB[2];
		queen WQ[9]; 
		king WKG;
		
		//Pe�as negras
		pawn BP[8];
		rook BR[2];
		knight BKN[2];
		bishop BB[2];
		queen BQ[9];
		king BKG;
		
		//Linha 0 -> Pe�es
		//Linha 1 -> Restante das pe�as
		piece *Wpieces[2][8]; 
		piece *Bpieces[2][8];
		
		//Validacao do movimento
		int movementValid();
		
	public:
		Game();
		bool printOld, printNew;
		bool printCheck;
		int oldPos[2], newPos[2];	
		int checkPos[2][2];
		int board[8][8];
		void Event_Left(int x, int y, int sizeX, int sizeY);
		void operator --();
		
};
