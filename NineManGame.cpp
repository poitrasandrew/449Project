#include "NineManGame.h"

std::string NineManGame::getcolorString(int i) {
	if (i == WHITE) {
		return "White";
	}
	else { return "Black"; }
}

void NineManGame::runWindow() {
	BackendBoard backend = BackendBoard();	// object for backend logic handling
	
	std::vector<Piece> white, black;		// vectors for both player's pieces
	for (int i = 0; i < 18; i = i + 2)
	{
		white.push_back(Piece(15.f, (i + 1) * 20, 50, sf::Color::White));
		black.push_back(Piece(15.f, (i + 1) * 20, 17, sf::Color(20, 20, 20, 255)));   // Color is slightly lighter than black to improve visibility of the pieces
	}

	Board gameBoard("board.png", "theimage.ttf");						// board setup
	window.create(sf::VideoMode(720, 720), "Nine Men's Morris");
	window.setFramerateLimit(60);

	sf::RectangleShape gameBackground(sf::Vector2f(720.f, 720.f));		// Create a solid color background that will go behind the game board
	gameBackground.setFillColor(sf::Color(140, 140, 140, 255));
	gameBackground.setPosition(sf::Vector2f(0.f, 0.f));

	bool isPlacementPhase = true;		// track initial game phase
	bool isRemovalPhase = false;		// track if a player can remove an opponent's piece
	//bool gameOver = false;				// track when game ends
	bool selected = false;				// track when piece is selected
	char winner = 'n';					// track winner of the game
	int selectedPiece;					// track which piece is selected
	int turn;							// track player turn	
	int whitePlacementCounter = 9;		// counter to know when placement phase is over
	int blackPlacementCounter = 9;

	// set initial turn from player input (use WHITE/BLACK constants from class header file)
	turn = WHITE;

	while (window.isOpen())
	{			
		if (whitePlacementCounter <= 0 && blackPlacementCounter <= 0) {		// enter movement phase once all pieces have been initially placed
			isPlacementPhase = false;
		}
		

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
							for (int i = 0; i < white.size(); i++) {
								if (white[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
									selected = true;
									selectedPiece = i;
									white[i].pieceShape.setOrigin(event.mouseButton.x - (white[i].pieceShape.getPosition().x - white[i].pieceShape.getOrigin().x),
										event.mouseButton.y - (white[i].pieceShape.getPosition().y - white[i].pieceShape.getOrigin().y));
								}
							}
						}
						else if (isRemovalPhase) {
							for (int i = 0; i < black.size(); i++) {
								if (black[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
									if (black[i].isPlaced() && backend.canRemove(black[i].getBoardRow(), black[i].getBoardCol(), BLACK)) {
										backend.updateBoard(black[i].getBoardRow(), black[i].getBoardCol(), EMPTY);
										black.erase(black.begin() + i);
										isRemovalPhase = false;
										changeTurn(turn);
									}
								}
							}
							break;
						}
					}
					else if (turn == BLACK) {
						if (!isRemovalPhase) {
							for (int i = 0; i < black.size(); i++) {
								if (black[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
									selected = true;
									selectedPiece = i;
									black[i].pieceShape.setOrigin(event.mouseButton.x - (black[i].pieceShape.getPosition().x - black[i].pieceShape.getOrigin().x),
										event.mouseButton.y - (black[i].pieceShape.getPosition().y - black[i].pieceShape.getOrigin().y));
								}
							}
						}
						else if (isRemovalPhase) {
							for (int i = 0; i < black.size(); i++) {
								if (white[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
									if (white[i].isPlaced() && backend.canRemove(white[i].getBoardRow(), white[i].getBoardCol(), WHITE)) {
										backend.updateBoard(white[i].getBoardRow(), white[i].getBoardCol(), EMPTY);
										white.erase(white.begin() + i);
										isRemovalPhase = false;
										changeTurn(turn);
									}
								}
							}
							break;
						}
					}
				}
			}

			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (turn == WHITE) {
						for (int i = 0; i < white.size(); i++) {
							if (white[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								selected = !selected;		// stop dragging piece on mouse release
								
								if (!isRemovalPhase) {		// if removal phase, do not process as piece movement
									white[i].convertTempCoordinates();

									if (!backend.isvalidPosition(white[i].getTempRow(), white[i].getTempCol())) {
										white[i].snapToOldPos();
										break;
									}

									if (whitePlacementCounter > 0) {			// do not move pieces that have already been placed until placement phase is over
										if (white[i].isPlaced()) {
											white[i].snapToOldPos();
											break;
										}
										if (!backend.isvalidPlacement(white[i].getTempRow(), white[i].getTempCol())) {
											white[i].snapToOldPos();
											break;
										}
										else {
											white[i].convertCoordinates();
											white[i].setPlaced();
											white[i].snapToNewPos();
											backend.updateBoard(white[i].getBoardRow(), white[i].getBoardCol(), WHITE);
											whitePlacementCounter--;
										}
									}
									else if (whitePlacementCounter <= 0) {
										if(!backend.isValidMove(white[i].getBoardRow(), white[i].getBoardCol(), white[i].getTempRow(), white[i].getTempCol(), white.size())) {
											white[i].snapToOldPos();
											break;
										}
										else {
											// update piece coordinates by passing the GUI coordinates to
											backend.updateBoard(white[i].getBoardRow(), white[i].getBoardCol(), EMPTY);
											white[i].convertCoordinates();
											white[i].snapToNewPos();
											backend.updateBoard(white[i].getBoardRow(), white[i].getBoardCol(), WHITE);
										}
									}

									if (backend.formsMill(white[i].getBoardRow(), white[i].getBoardCol(), WHITE)) {
										isRemovalPhase = true;
										backend.printBoard();
										break;
									}
									else {
										changeTurn(turn);
									}
								}
								
								backend.printBoard();		// print updated backend board for console logging
							}
						}
					}
					else if (turn == BLACK) {
						for (int i = 0; i < black.size(); i++) {
							if (black[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								selected = !selected;
								if (!isRemovalPhase) {		// if removal phase, do not process as piece movement
									black[i].convertTempCoordinates();

									if (!backend.isvalidPosition(black[i].getTempRow(), black[i].getTempCol())) {
										black[i].snapToOldPos();
										break;
									}

									if (blackPlacementCounter > 0) {			// do not move pieces that have already been placed until placement phase is over
										if (black[i].isPlaced()) {
											black[i].snapToOldPos();
											break;
										}
										if (!backend.isvalidPlacement(black[i].getTempRow(), black[i].getTempCol())) {
											black[i].snapToOldPos();
											break;
										}
										else {
											black[i].convertCoordinates();
											black[i].setPlaced();
											black[i].snapToNewPos();
											backend.updateBoard(black[i].getBoardRow(), black[i].getBoardCol(), BLACK);
											blackPlacementCounter--;
										}
									}
									else if (blackPlacementCounter <= 0) {
										if (!backend.isValidMove(black[i].getBoardRow(), black[i].getBoardCol(), black[i].getTempRow(), black[i].getTempCol(), black.size())) {
											black[i].snapToOldPos();
											break;
										}
										else {
											// update piece coordinates by passing the GUI coordinates to
											backend.updateBoard(black[i].getBoardRow(), black[i].getBoardCol(), EMPTY);
											black[i].convertCoordinates();
											black[i].snapToNewPos();
											backend.updateBoard(black[i].getBoardRow(), black[i].getBoardCol(), BLACK);
										}
									}

									if (backend.formsMill(black[i].getBoardRow(), black[i].getBoardCol(), BLACK)) {
										isRemovalPhase = true;
										backend.printBoard();
										break;
									}
									else {
										changeTurn(turn);
									}
								}
								backend.printBoard();		// print updated backend board for console logging
							}
						}
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

void NineManGame::changeTurn(int &currentTurn) {
	if (currentTurn == WHITE) {
		currentTurn = BLACK;
	}
	else {
		currentTurn = WHITE;
	}
	std::cout << "It is currently " << NineManGame::getcolorString(currentTurn) << "'s turn." << std::endl;
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

	sf::Text yes("Yes", font, 28);
	yes.setOutlineColor(sf::Color::Black);
	yes.setOutlineThickness(3);
	yes.setPosition(218, 330);

	sf::Text no("No", font, 28);
	no.setOutlineColor(sf::Color::Black);
	no.setOutlineThickness(3);
	no.setPosition(461, 330);
	std::cout << "Ending the game." << std::endl;
	switch (winner) {
	case 'w':
		window.draw(endGameOverlay);
		window.draw(whiteVictory);
		window.draw(playAgain);
		window.draw(yes);
		window.draw(no);
		// still need to make "yes" and "no" clickable buttons
		break;
	case 'b':
		window.draw(endGameOverlay);
		window.draw(blackVictory);
		window.draw(playAgain);
		window.draw(yes);
		window.draw(no);
		// still need to make "yes" and "no" clickable buttons
		break;
	}
}