#include "BackendBoard.h"
#include "NineManGame.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

bool BackendBoard::formsMill(int startRow, int startCol, int player) {
	// function to traverse array from given position in each direction to search for mill

	int i = startRow;
	int j = startCol;
	int oppPlayer;
	int result;					// stores result from each individual direction check
	int millCount = 1;			// used to count number of pieces "in line" of the same player, if it equals 3,
								// there is a mill. Initialized to 1 to include current piece.
	
	if (player == NineManGame::WHITE) {		// denote opposite player for array traversal
		oppPlayer = NineManGame::BLACK;
	}
	else { oppPlayer = NineManGame::WHITE; }


	// Vertical Mills
	while (--i >= NineManGame::ROWMIN) {	// check upwards
		result = millDirectionCheck(i, startCol, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) { 
			std::cout << "Mill formed by piece at (" << startRow << ", " << startCol << ")" << std::endl;
			return true; 
		}
	}
	i = startRow;			// reset row position
	while (++i < NineManGame::ROWMAX) {	// check downwards
		result = millDirectionCheck(i, startCol, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) {
			std::cout << "Mill formed by piece at (" << startRow << ", " << startCol << ")" << std::endl;
			return true;
		}
	}

	millCount = 1;			// reset millCount for search in other direction

	// Horizontal Mills
	while (--j >= NineManGame::COLMIN) {	// check leftwards
		result = millDirectionCheck(startRow, j, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) {
			std::cout << "Mill formed by piece at (" << startRow << ", " << startCol << ")" << std::endl;
			return true;
		}
	}
	j = startCol;			// reset column position
	while (++j < NineManGame::COLMAX) {	// check rightwards
		result = millDirectionCheck(startRow, j, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) {
			std::cout << "Mill formed by piece at (" << startRow << ", " << startCol << ")" << std::endl;
			return true;
		}
	}
	std::cout << "No mill formed by piece at (" << startRow << ", " << startCol << ")" << std::endl;
	return false;
}

int BackendBoard::millDirectionCheck(int i, int j, int &millCount, int player, int oppPlayer) {
	// check if position in question contains a piece that can be used in player's mill

	if ((i == 3) && (j == 3)) {					// avoid crossing middle - impossible mill
		return -1;
	}
	else if (board[i][j] == player) {		// add to millCount if same player
		millCount++;
		return 1;
	}
	else if (board[i][j] == oppPlayer || board[i][j] == NineManGame::EMPTY) {	
											// stop searching that direction if opposite
		return -1;							// player's piece or empty space is in way
	}
	return 0;								// no action, but keep searching
}

 bool BackendBoard::canRemove(int row, int col, int player) {
	 if (!formsMill(row, col, player)) {		// return true if piece is not in mill
		 std::cout << "Can remove piece at (" << row << ", " << col << ") - not in mill." << std::endl;
		 return true;
	}
	 else {										// if piece is in mill, check if any other pieces are in a mill
		 for (int i = 0; i < NineManGame::ROWMAX; i++) {
			 for (int j = 0; j < NineManGame::COLMAX; j++) {
				 if (board[i][j] == player) {
					 if (!formsMill(i, j, player)) {	// if another piece is not in a mill, return false
						 std::cout << "Cannot remove piece at (" << row << ", " << col << ") - there is another piece not in a mill." << std::endl;
						 return false;					// since a different piece must be removed first
					 }
				 }
			 }
		 }
	 }
	 std::cout << "Can remove piece at (" << row << ", " << col << ") - all others in mill also." << std::endl;
	 return true;							// if all other pieces are in a mill, the selected piece can be removed
} 

bool BackendBoard::isvalidPosition(int row, int col)
{
	if (row == NineManGame::INVALID || col == NineManGame::INVALID) {
		//std::cout << "(" << row << "," << col << ") is an invalid position." << std::endl;
		return false;
	}
	if (row == 3 && col == 3) {				// cannot place piece in middle
		//std::cout << "(" << row << "," << col << ") is an invalid position." << std::endl;
		return false;
	}
	if (row == col || row == 3 || col == 3 || row + col == 6) {		// acceptance cases
		//std::cout << "(" << row << "," << col << ") is a valid position." << std::endl;
		return true;
	}
	else {
		//std::cout << "(" << row << "," << col << ") is an invalid position." << std::endl;
		return false;
	}
}

bool BackendBoard::isvalidPlacement(int row, int col) {
	if (board[row][col] == NineManGame::EMPTY) {
		std::cout << "(" << row << "," << col << ") is a valid placement." << std::endl;
		return true;
	}
	else {
		std::cout << "(" << row << "," << col << ") is a invalud placement: space not empty." << std::endl;
		return false;
	}
}

bool BackendBoard::isValidMove(int origRow, int origCol, int newRow, int newCol, int pieceCount) {
	// check if empty
	if (board[newRow][newCol] != 0) {
		/*std::cout << "Invalid Move (" << origRow << ", " << origCol << ") to ("
			<< newRow << ", " << newCol << "): Destination is not empty." << std::endl;*/
		return false;
	}

	// check if player can fly
	if (pieceCount <= 3) {
		/*std::cout << "Valid Move (" << origRow << ", " << origCol << ") to ("
			<< newRow << ", " << newCol << "): Can Fly" << std::endl;*/
		return true;			// any movement to empty space is valid when flying
	}

	// check if diagonal
	if ((origRow != newRow) && (origCol != newCol)) {
		/*std::cout << "Invalid Move (" << origRow << ", " << origCol << ") to ("
			<< newRow << ", " << newCol << "): Path is diagonal." << std::endl;*/
		return false;
	}

	int i = origRow;
	int j = origCol;

	// check if adjacent - two spaces are adjacent if there are only invalid spaces between them, except (3,3)
	// row check
	while (newRow < --i) {
		if (board[i][origCol] != -1 || (i == 3 && origCol == 3)) {
			/*std::cout << "Invalid Move (" << origRow << ", " << origCol << ") to ("
				<< newRow << ", " << newCol << "): Impossible vertical move." << std::endl;*/
			return false;
		}
	}
	i = origRow;		// reset row index
	while (newRow > ++i) {
		if (board[i][origCol] != -1 || (i == 3 && origCol == 3)) {
			/*std::cout << "Invalid Move (" << origRow << ", " << origCol << ") to ("
				<< newRow << ", " << newCol << "): Impossible vertical move." << std::endl;*/
			return false;
		}
	}
	// column check
	while (newCol < --j) {
		if (board[origRow][j] != -1 || (origRow == 3 && j == 3)) {
			/*std::cout << "Invalid Move (" << origRow << ", " << origCol << ") to ("
				<< newRow << ", " << newCol << "): Impossible horizontal move." << std::endl;*/
			return false;
		}
	}
	j = origCol;  // reset column index
	while (newCol > ++j) {
		if (board[origRow][j] != -1 || (origRow == 3 && j == 3)) {
			/*std::cout << "Invalid Move (" << origRow << ", " << origCol << ") to ("
				<< newRow << ", " << newCol << "): Impossible horizontal move." << std::endl;*/
			return false;
		}
	}
	/*std::cout << "Valid Move (" << origRow << ", " << origCol << ") to ("
		<< newRow << ", " << newCol << ")" << std::endl;*/
	return true;
}

bool BackendBoard::isLoser(int pieceCount, int player) {
	if (pieceCount < 3) {			// player loses if piece count is less than 3
		std::cout << NineManGame::getcolorString(player) << "loses: has less than 3 pieces left."
			<< std::endl;
		return true;
	}

	if (pieceCount == 3) {			// player can fly, so there is an empty spot on the board to move to
		
		return false;
	}

	// check if any valid moves available
	for (int i = 0; i < NineManGame::ROWMAX; i++) {
		for (int j = 0; j < NineManGame::COLMAX; j++) {
			if (board[i][j] == player) {
				if (!loserDirectionCheck(i, j)) {
		
					return false;		// if there is a valid move in that direction, player is not a loser
				}
			}
		}
	}
	std::cout << NineManGame::getcolorString(player) << "loses: no valid moves left."
		<< std::endl;
	return true;
}

bool BackendBoard::loserDirectionCheck(int startRow, int startCol) {
	// checks each direction for nearest point (first adjacent in given direction)
	// and returns false if a piece can be moved to that point (since a valid move exists, not a loser)
	int i = startRow;
	int j = startCol;

	while (--i >= NineManGame::ROWMIN) {	// check upwards
		if (board[i][startCol] != -1) {
			if (isValidMove(startRow, startCol, i, startCol, 9)) {
				return false;
			}
			else { break; }			// stop searching if move is invalid, no moves that direction
		}
	}
	i = startRow;							// reset row index
	while (++i < NineManGame::ROWMAX) {		// check downwards
		if (board[i][startCol] != -1) {
			if (isValidMove(startRow, startCol, i, startCol, 9)) {
				return false;
			}
			else { break; }
		}
	}
	while (--j >= NineManGame::COLMIN) {	// check leftwards
		if (board[startRow][j] != -1) {
			if (isValidMove(startRow, startCol, startRow, j, 9)) {
				return false;
			}
			else { break; }
		}
	}
	j = startCol;							// reset col index
	while (++j < NineManGame::COLMAX) {		// check rightwards
		if (board[startRow][j] != -1) {
			if (isValidMove(startRow, startCol, startRow, j, 9)) {
				return false;
			}
			else { break; }
		}
	}


	return true;			// if no valid moves, player is loser
}

void BackendBoard::findComputerMove(std::vector<Piece> &color, std::vector<Piece> &oppColor, bool &isRemovalPhase, int &placementCounter, int &turn) {
	// for placement, loop through to see if it can form mill, else, choose random spot
	// for movement, loop through each piece to see if a valid move can form a mill, else make a random move
	// for removing a piece, choose the first one that can be removed

	int randomRow = (rand() % (NineManGame::ROWMAX - 1)) + NineManGame::ROWMIN;
	int randomCol = (rand() % (NineManGame::COLMAX - 1)) + NineManGame::COLMIN;
	int randomIndex = (rand() % (color.size() - 1)) + 0;

	if (isRemovalPhase) {							// removal phase
		for (int i = 0; i < oppColor.size(); i++) {
			if (oppColor[i].isPlaced() && canRemove(oppColor[i].getBoardRow(), oppColor[i].getBoardCol(), NineManGame::getOppositePlayer(turn))) {
				updateBoard(oppColor[i].getBoardRow(), oppColor[i].getBoardCol(), NineManGame::EMPTY);
				oppColor.erase(oppColor.begin() + i);			// loop through opponent's pieces to find one that can be removed and remove it
				isRemovalPhase = false;
				return;
			}
		}
	}

	if (placementCounter > 0) {						// placement phase
		for (int i = 0; i < NineManGame::ROWMAX; i++) {
			for (int j = 0; j < NineManGame::COLMAX; j++) {
				if (isvalidPosition(i, j) && isvalidPlacement(i, j) && formsMill(i, j, turn)) {		// if placement forms mill, place piece there
					color[placementCounter-1].setBoardCoordinates(i, j);
					color[placementCounter-1].setPlaced();
					color[placementCounter-1].snapToNewPos();
					isRemovalPhase = true;
					updateBoard(color[placementCounter-1].getBoardRow(), color[placementCounter-1].getBoardCol(), turn);
					placementCounter--;
					return;
				}
			}
		}																	// otherwise, make random placement
		while (!(isvalidPosition(randomRow, randomCol) && isvalidPlacement(randomRow, randomCol))) {
			randomRow = (rand() % (NineManGame::ROWMAX - 1)) + NineManGame::ROWMIN;
			randomCol = (rand() % (NineManGame::COLMAX - 1)) + NineManGame::COLMIN;
		}
		color[placementCounter-1].setBoardCoordinates(randomRow, randomCol);
		color[placementCounter-1].setPlaced();
		color[placementCounter-1].snapToNewPos();
		updateBoard(color[placementCounter-1].getBoardRow(), color[placementCounter-1].getBoardCol(), turn);
		placementCounter--;
		return;
	}
	else if (placementCounter <= 0) {					// movement phase
			// for movement, loop through each piece to see if a valid move can form a mill, else make a random move
		for (int i = 0; i < NineManGame::ROWMAX; i++) {
			for (int j = 0; j < NineManGame::COLMAX; j++) {		// loop through backend board
				if (isvalidPosition(randomRow, randomCol) && formsMill(i, j, turn)) {					// if a mill can be formed, see if a piece can be moved there
					for (int p = 0; p < color.size(); p++) {	// if so, move it there
						if (isValidMove(color[p].getBoardRow(), color[p].getBoardCol(), i, j, color.size())) {
							updateBoard(color[p].getBoardRow(), color[p].getBoardCol(), NineManGame::EMPTY);
							color[p].setBoardCoordinates(i, j);
							color[p].snapToNewPos();
							updateBoard(color[p].getBoardRow(), color[p].getBoardCol(), turn);

							if (formsMill(color[p].getBoardRow(), color[p].getBoardCol(), turn)) {		// verify that a mill was formed
								isRemovalPhase = true;												
							}
							return;
						}
					}
				}
			}
		}														// else, make a random move
		while (!(isvalidPosition(randomRow, randomCol) && isValidMove(color[randomIndex].getBoardRow(), color[randomIndex].getBoardCol(), randomRow, randomCol, color.size()))) {	// find a random valid move for that piece
			std::cout << "Invalid Random Move." << std::endl;				// find a random piece that can be moved to a random position
			randomIndex = (rand() % (color.size() - 1)) + 0;
			randomRow = (rand() % (NineManGame::ROWMAX - 1)) + NineManGame::ROWMIN;
			randomCol = (rand() % (NineManGame::COLMAX - 1)) + NineManGame::COLMIN;
		}
		updateBoard(color[randomIndex].getBoardRow(), color[randomIndex].getBoardCol(), NineManGame::EMPTY);		// make the random move
		color[randomIndex].setBoardCoordinates(randomRow, randomCol);
		color[randomIndex].snapToNewPos();
		isRemovalPhase = false; 
		updateBoard(color[randomIndex].getBoardRow(), color[randomIndex].getBoardCol(), turn);
		return;
	}
}

void BackendBoard::updateBoard(int row, int col, int val) {
	board[row][col] = val;
	std::cout << "Position Updated: row: " << row << ", column: " << col << " is now " << val << std::endl;
}

void BackendBoard::printBoard() {		//utility function to visualize backend logic "board"
	for (int i = 0; i < NineManGame::ROWMAX; i++) {
		std::cout << "{ ";
		for (int j = 0; j < NineManGame::COLMAX; j++) {
			std::cout << std::setw(2) << std::right << board[i][j] << " ";
		}
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;
}

BackendBoard::BackendBoard() {
	std::cout << "Backend Board Created." << std::endl;
	srand((unsigned)time(0));		// init pseudo-random number generator
	printBoard();	// show initial board
}

BackendBoard::~BackendBoard() {}