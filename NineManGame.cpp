#include "NineManGame.h"

std::string NineManGame::getcolorString(int i) {
	if (i == WHITE) {
		return "White";
	}
	else { return "Black"; }
}

void NineManGame::runWindow(int goesFirst, int gameplayType) {

	backend = BackendBoard();			// backend init
	for (int i = 0; i < 18; i = i + 2)	// piece vectors setup
	{
		white.push_back(Piece(15.f, (i + 1) * 20, 50, sf::Color::White));
		black.push_back(Piece(15.f, (i + 1) * 20, 17, sf::Color(20, 20, 20, 255)));   // Color is slightly lighter than black to improve visibility of the pieces
	}
	Board gameBoard("board.png", "theimage.ttf");						// GUI board setup
	sf::RectangleShape gameBackground(sf::Vector2f(720.f, 720.f));		// Create a solid color background that will go behind the game board
	gameBackground.setFillColor(sf::Color(140, 140, 140, 255));
	gameBackground.setPosition(sf::Vector2f(0.f, 0.f));
	window.create(sf::VideoMode(720, 720), "Nine Men's Morris");		// window settings
	window.setFramerateLimit(60);

	gameType = gameplayType;			// set game type to single/two player
	turn = goesFirst;					// set initial turn from player input

	while (window.isOpen())
	{
		if (whitePlacementCounter <= 0 && blackPlacementCounter <= 0) {		// enter movement phase once all pieces have been initially placed
			isPlacementPhase = false;
		}

		if (isComputerTurn) {			// computer move handling
			Sleep(500);					// sleep thread for half a second to emulate real decision making
			if (turn == WHITE) {
				computerMove(white, black, backend, isRemovalPhase, whitePlacementCounter, turn);
			}
			else {
				computerMove(black, white, backend, isRemovalPhase, blackPlacementCounter, turn);
			}
			backend.printBoard();
		}
		else {							// human move handling
			sf::Event event;
			while (window.pollEvent(event))
			{
				//end loop when window closes
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				//changes origin of the moved dot to make dragging more intuitive on left click
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (turn == WHITE) {
							if (!isRemovalPhase) {
								clickToMovePiece(white, event, selected, selectedPiece);
							}
							else if (isRemovalPhase) {
								clickToRemovePiece(black, event, backend, isRemovalPhase, turn);
								if (isRemovalPhase) { break; } // skip piece movement when piece to be removed is invalid (try again)
							}									// (i.e. if it is still removal phase, break)
						}
						else if (turn == BLACK) {
							if (!isRemovalPhase) {
								clickToMovePiece(black, event, selected, selectedPiece);
							}
							else if (isRemovalPhase) {
								clickToRemovePiece(white, event, backend, isRemovalPhase, turn);
								if (isRemovalPhase) { break; } // skip piece movement when piece to be removed is invalid (try again)
							}									// (i.e. if it is still removal phase, break)
						}
					}
				}

				else if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (turn == WHITE) {
							onPieceRelease(white, event, selected, backend, isRemovalPhase, whitePlacementCounter, turn);
						}
						else if (turn == BLACK) {
							onPieceRelease(black, event, selected, backend, isRemovalPhase, blackPlacementCounter, turn);
						}
					}
				}

				//move the dot around when one has been selected
				if (selected) {
					if (turn == WHITE) {
						white[selectedPiece].pieceShape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					}
					else {
						black[selectedPiece].pieceShape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					}
				}
			}
	}
		window.clear();

		window.draw(gameBackground);
		gameBoard.drawBoard(window);
		Piece::drawPieces(window, white);
		Piece::drawPieces(window, black);
		displayTurn(turn);

		if (!isPlacementPhase) {
			if (backend.isLoser(white.size(), WHITE)) {
				winner = 'b';		// white loses, end game, show results
				declareWinner(winner);
			}
			else if (backend.isLoser(black.size(), BLACK)) {
				winner = 'w';		// black loses, end game, show results
				declareWinner(winner);
			}
		}

		window.display();
	}
	return;
}

void NineManGame::clickToMovePiece(std::vector<Piece> &color, sf::Event event, bool &selected, int &selectedPiece) {
	for (int i = 0; i < color.size(); i++) {
		if (color[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			selected = true;
			selectedPiece = i;
			color[i].pieceShape.setOrigin(event.mouseButton.x - (color[i].pieceShape.getPosition().x - color[i].pieceShape.getOrigin().x),
				event.mouseButton.y - (color[i].pieceShape.getPosition().y - color[i].pieceShape.getOrigin().y));
		}
	}
}

void NineManGame::clickToRemovePiece(std::vector<Piece> &color, sf::Event event, BackendBoard &backend, bool &isRemovalPhase, int &turn) {
	for (int i = 0; i < color.size(); i++) {
		if (color[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			if (color[i].isPlaced() && backend.canRemove(color[i].getBoardRow(), color[i].getBoardCol(), getOppositePlayer(turn))) {
				backend.updateBoard(color[i].getBoardRow(), color[i].getBoardCol(), EMPTY);
				color.erase(color.begin() + i);
				isRemovalPhase = false;
				changeTurn(turn, gameType, isComputerTurn);
			}
		}
	}
}

int NineManGame::getOppositePlayer(int turn) {
	if (turn == NineManGame::WHITE) {
		return NineManGame::BLACK;
	}
	else { return NineManGame::WHITE; }
}

void NineManGame::onPieceRelease(std::vector<Piece> &color, sf::Event event, bool &selected, BackendBoard &backend, bool &isRemovalPhase, int &placementCounter, int &turn) {
	for (int i = 0; i < color.size(); i++) {
		if (color[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			selected = !selected;		// stop dragging piece on mouse release

			if (!isRemovalPhase) {		// if removal phase, do not process as piece movement
				color[i].convertTempCoordinates();

				if (!backend.isvalidPosition(color[i].getTempRow(), color[i].getTempCol())) {
					color[i].snapToOldPos();
					break;
				}
				if (placementCounter > 0) {			// do not move pieces that have already been placed until placement phase is over
					if (color[i].isPlaced()) {
						color[i].snapToOldPos();
						break;
					}
					if (!backend.isvalidPlacement(color[i].getTempRow(), color[i].getTempCol())) {
						color[i].snapToOldPos();
						break;
					}
					else {
						color[i].convertCoordinates();
						color[i].setPlaced();
						color[i].snapToNewPos();
						backend.updateBoard(color[i].getBoardRow(), color[i].getBoardCol(), turn);
						placementCounter--;
					}
				}
				else if (placementCounter <= 0) {
					if (!backend.isValidMove(color[i].getBoardRow(), color[i].getBoardCol(), color[i].getTempRow(), color[i].getTempCol(), color.size())) {
						color[i].snapToOldPos();
						break;
					}
					else {
						// update piece coordinates by passing the GUI coordinates to
						backend.updateBoard(color[i].getBoardRow(), color[i].getBoardCol(), EMPTY);
						color[i].convertCoordinates();
						color[i].snapToNewPos();
						backend.updateBoard(color[i].getBoardRow(), color[i].getBoardCol(), turn);
					}
				}

				if (backend.formsMill(color[i].getBoardRow(), color[i].getBoardCol(), turn)) {
					isRemovalPhase = true;
					backend.printBoard();
					break;
				}
				else {
					changeTurn(turn, gameType, isComputerTurn);
				}
			}

			backend.printBoard();		// print updated backend board for console logging
		}
	}
}

void NineManGame::changeTurn(int &currentTurn, int gameType, bool &computerTurn) {
	if (currentTurn == WHITE) {
		currentTurn = BLACK;
	}
	else {
		currentTurn = WHITE;
	}
	std::cout << "It is currently " << NineManGame::getcolorString(currentTurn) << "'s turn." << std::endl;

	if (gameType == SINGLE_PLAYER) {
		computerTurn = !computerTurn;
	}
}

void NineManGame::displayTurn(int &currentTurn) {
	sf::Font font;														// Creates a font to be used by displayed text
	if (!font.loadFromFile("NotoSansJP-Black.otf")) {
		std::cout << "Cannot find the font file 'NotoSansJP-Black.otf' make sure it is in the same folder as NineManGame.cpp" << std::endl;
	}

	sf::Text whiteTurn("It is currently White's turn", font, 20);		// The following "sf::Text" code blocks create and stylize text objects that are displayed later in the current function
	whiteTurn.setOutlineColor(sf::Color::Black);
	whiteTurn.setOutlineThickness(2);
	whiteTurn.setPosition(410, 35);

	sf::Text blackTurn("It is currently Black's turn", font, 20);
	blackTurn.setOutlineColor(sf::Color::Black);
	blackTurn.setOutlineThickness(2);
	blackTurn.setPosition(410, 35);

	switch (currentTurn) {								// draw text on screen displaying who's turn it is
	case 1:
		window.draw(whiteTurn);
		break;
	case 2:
		window.draw(blackTurn);
		break;
	}
}

void NineManGame::declareWinner(char winner) {
	sf::RectangleShape endGameOverlay(sf::Vector2f(720.f, 720.f));		// Create a dark transparent overlay to use for game results background
	endGameOverlay.setFillColor(sf::Color(0, 0, 0, 215));
	endGameOverlay.setPosition(sf::Vector2f(0.f, 0.f));

	sf::Font font;														// Creates a font to be used by displayed text
	if (!font.loadFromFile("NotoSansJP-Black.otf")) {
		std::cout << "Cannot find the font file 'NotoSansJP-Black.otf' make sure it is in the same folder as NineManGame.cpp" << std::endl;
	}

	sf::Text whiteVictory("White has won the game!", font, 40);
	whiteVictory.setOutlineColor(sf::Color::Black);
	whiteVictory.setOutlineThickness(4);
	whiteVictory.setPosition(105, 140);

	sf::Text blackVictory("Black has won the game!", font, 40);
	blackVictory.setOutlineColor(sf::Color::Black);
	blackVictory.setOutlineThickness(4);
	blackVictory.setPosition(105, 140);

	sf::Text playAgain("Would you like to play again?", font, 28);
	playAgain.setOutlineColor(sf::Color::Black);
	playAgain.setOutlineThickness(3);
	playAgain.setPosition(155, 280);

	
	Button yes("Yes", 50, 50, 218, 330, 28, sf::Color::Transparent);

	Button no("No", 50, 50, 461, 330, 28, sf::Color::Transparent);

	std::cout << "Ending the game." << std::endl;
	switch (winner) {
	case 'w':
		window.draw(endGameOverlay);
		window.draw(whiteVictory);
		window.draw(playAgain);
		yes.draw(window);
		no.draw(window);
		break;
	case 'b':
		window.draw(endGameOverlay);
		window.draw(blackVictory);
		window.draw(playAgain);
		yes.draw(window);
		no.draw(window);
		break;
	}
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (yes.clicked(event)) {
			window.close();
			NineManGame game;
			game.runWindow(turn, gameType);
		}
		if (no.clicked(event)) {
			window.close();
		}
	}
}

void NineManGame::computerMove(std::vector<Piece> &color, std::vector<Piece> &oppColor, BackendBoard &backend, bool &isRemovalPhase, int &placementCounter, int &turn) {
	backend.findComputerMove(color, oppColor, isRemovalPhase, placementCounter, turn);		// finds move and updates GUI
			// TODO: let this method update GUI instead of backend

	if (!isRemovalPhase) {									// if computer did not form a mill, change the turn
		changeTurn(turn, gameType, isComputerTurn);			// otherwise, wait for next loop iteration to remove a piece and complete turn
	}
}