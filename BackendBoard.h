#pragma once

class BackendBoard {
public:

private:
	int board[7][7] = { 0,-1,-1, 0,-1,-1, 0 
					   -1, 0,-1, 0,-1, 0,-1,
					   -1,-1, 0, 0, 0,-1,-1,
					    0, 0, 0,-1, 0, 0, 0,
					   -1,-1, 0, 0, 0,-1,-1,
					   -1, 0,-1, 0,-1, 0,-1,
					    0,-1,-1, 0,-1,-1, 0 };
	//For board position identification
	//-1 = invalid
	// 0 = empty valid
	// 1 = white
	// 2 = black
 };