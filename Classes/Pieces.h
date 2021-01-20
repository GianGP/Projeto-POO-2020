class piece
{
	protected:
		bool white;
		int ID;
		int position[2];
	public:
		piece();
		piece(bool color, int posX, int posY, int number);
		void move(int newPos[2], int board [8][8]);
		void setData(bool color, int posX, int posY, int number);
};

class pawn : public piece
{
	public:
		pawn();
		pawn(bool color, int posX, int posY, int number);
		int validMovement (int newPos[2], int board[][8]);
};

class bishop : public piece
{
	public:
		bishop();
		bishop(bool color, int posX, int posY, int number);
		int validMovement(int newPos[2], int board[][8]);
};

class rook : public piece
{
	public:
		bool castling;
		rook();
		rook(bool color, int posX, int posY, int number);
		int validMovement(int newPos[2], int board[][8]);
		void setData (bool inputCastling);
};

class knight : public piece
{
	public:
		knight();
		knight(bool color, int posX, int posY, int number);		
		int validMovement (int newPos[2], int board[][8]);
};

class queen : public bishop, rook
{
	public:
		queen();
		queen(bool color, int posX, int posY, int number);
		int validMovement(int newPos[2], int board[][8]);
		void updateValue();
};

class king : public piece
{
	public:
		bool castling;
		king();
		king(bool color, int posX, int posY, int number);
		int validMovement (int newPos[2], int board[][8]);
		void setData (bool inputCastling);
};
