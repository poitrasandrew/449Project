#pragma once
#include "Piece.h"

class BackendBoard {
public:
	bool isvalidPosition(int row, int col);
	bool isvalidPlacement(int row, int col);
	bool isValidMove(int origRow, int origCol, int newRow, int newCol);
	bool formsMill(int startRow, int startCol, int player);
	int millDirectionCheck(int i, int j, int &millCount, int player, int oppPlayer);
	bool canRemove(int row, int col, int player); 
	void updateBoard(int row, int col, int val);
	void printBoard();
	bool isLoser(int pieceCount, int player);
	bool loserDirectionCheck(int startRow, int startCol);
	BackendBoard();
	~BackendBoard();
private:
	

	int board[7][7] = { { 0,-1,-1, 0,-1,-1, 0},
						{-1, 0,-1, 0,-1, 0,-1},
						{-1,-1, 0, 0, 0,-1,-1},
						{ 0, 0, 0,-1, 0, 0, 0}, 
						{-1,-1, 0, 0, 0,-1,-1},
						{-1, 0,-1, 0,-1, 0,-1},
						{ 0,-1,-1, 0,-1,-1, 0} }; 

	//For board position identification
	//-1 = invalid
	// 0 = empty valid
	// 1 = white
	// 2 = black
 };