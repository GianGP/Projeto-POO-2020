class piece
{
	protected:
		bool white, alive;
		int position[2];
		int ID;
	public:
		void move(int newPos[2], int board [8][8]);
		void setData(int pos[2], bool old);
		piece(bool color, bool state, int posX, int posY, int number);
};

class pawn : public piece
{
	public:
		pawn(bool color, bool state, int posX, int posY, int number);
		int validMovement (int oldPos[2], int newPos[2], int board[][8]);
};

class bishop : public piece
{
	public:
		int validMovement(int oldPos[2], int newPos[2], int board[][8]);
		bishop(bool color, bool state, int posX, int posY, int number);
};

class rook : public piece
{
	public:
		int validMovement(int oldPos[2], int newPos[2], int board[][8]);
		rook(bool color, bool state, int posX, int posY, int number);
};

class knight : public piece
{
	public:
		knight(bool color, bool state, int posX, int posY, int number);		
		int validMovement (int oldPos[2], int newPos[2], int board[][8]);
};

class queen : public bishop, rook
{
	public:
		int validMovement(int oldPos[2], int newPos[2], int board[][8]);
		queen(bool color1, bool state1, int posX1, int posY1, int number1, bool color2, bool state2, int posX2, int posY2, int number2);
};

class king : public piece
{
	public:
		king(bool color, bool state, int posX, int posY, int number);
		int validMovement (int oldPos[2], int newPos[2], int board[][8]);
};
