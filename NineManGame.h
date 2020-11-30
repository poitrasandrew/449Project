#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "BackendBoard.h"
#include "Piece.h"
#include "Button.h"

#pragma once
class NineManGame
{
public:
	static const int ROWMAX = 7, COLMAX = 7, ROWMIN = 0, COLMIN = 0;	// edge array positions
	static const int INVALID = -1, EMPTY = 0, WHITE = 1, BLACK = 2;		// array value definitions
	static std::string getcolorString(int i);

	void runWindow(int goesFirst);
	void clickToMovePiece(std::vector<Piece> &color, sf::Event event, bool &selected, int &selectedPiece);
	void clickToRemovePiece(std::vector<Piece> &oppColor, sf::Event event, BackendBoard &backend, bool &isRemovalPhase, int &turn);
	int getOppositePlayer(int turn);
	void onPieceRelease(std::vector<Piece> &color, sf::Event event, bool &selected, BackendBoard &backend, bool &isRemovalPhase, int &placementCounter, int &turn);
	void computerMove(std::vector<Piece> &color, sf::Event event, bool &selected, int &selectedPiece, BackendBoard &backend, bool &isRemovalPhase, int &turn);
			// TODO: need to implement, will call backend computer move, have backend coords assigned, and then update GUI
	void changeTurn(int &currentTurn);
	void displayTurn(int &currentTurn);
	void declareWinner(char winner);
private:
	sf::RenderWindow window;
	int turn;							// track player turn	
};
