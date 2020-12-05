#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
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
	static const int SINGLE_PLAYER = 1, TWO_PLAYER = 2;					// game type definitions
	static std::string getcolorString(int i);

	void runWindow(int goesFirst, int gameplayType);
	void clickToMovePiece(std::vector<Piece> &color, sf::Event event, bool &selected, int &selectedPiece);
	void clickToRemovePiece(std::vector<Piece> &oppColor, sf::Event event, BackendBoard &backend, bool &isRemovalPhase, int &turn);
	int static getOppositePlayer(int turn);
	void onPieceRelease(std::vector<Piece> &color, sf::Event event, bool &selected, BackendBoard &backend, bool &isRemovalPhase, int &placementCounter, int &turn);
	void computerMove(std::vector<Piece> &color, std::vector<Piece> &oppColor, BackendBoard &backend, bool &isRemovalPhase, int &placementCounter, int &turn);
	void changeTurn(int &currentTurn, int gameType, bool &computerTurn);
	void displayTurn(int &currentTurn);
	void declareWinner(char winner);
private:
	sf::RenderWindow window;
	BackendBoard backend;				// object for backend logic handling
	std::vector<Piece> white, black;	// vectors for both player's pieces

	int gameType;						// track game type (single or two player)
	int turn;							// track player turn
	bool isComputerTurn = false;		// track computer turn, player goes first as chosen color
	bool isPlacementPhase = true;		// track initial game phase
	bool isRemovalPhase = false;		// track if a player can remove an opponent's piece
	bool selected = false;				// track when piece is selected
	char winner = 'n';					// track winner of the game
	int selectedPiece;					// track which piece is selected
	int whitePlacementCounter = 9;		// counter to know when placement phase is over
	int blackPlacementCounter = 9;
};
