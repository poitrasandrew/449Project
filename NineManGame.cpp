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
		white.push_back(Piece(15.f, (i + 1) * 20, 50, sf::Color::Yellow));
		black.push_back(Piece(15.f, (i + 1) * 20, 17, sf::Color::Red));
	}

	Board gameBoard("board.png", "theimage.ttf");		// board setup
	window.create(sf::VideoMode(720, 720), "9 Men's Morris");
	window.setFramerateLimit(60);

	bool isPlacementPhase = true;		// track initial game phase
	bool isRemovalPhase = false;		// track if a player can remove an opponent's piece
	bool gameOver = false;				// track when game ends
	bool selected = false;				// track when piece is selected
	int selectedPiece;					// track which piece is selected
	int turn;							// track player turn	
	int placementCounter = 18;			// counter to know when placement phase is over

	// set initial turn from player input (use WHITE/BLACK constants from class header file)
	turn = WHITE;

	while (window.isOpen())
	{
											//Game over check
		/*if (!isPlacementPhase) {			// TODO: adjust to acccount for ending game in placement phase
			if (turn == WHITE && backend.isLoser(white.size(), turn)) {
				// white loses, end game, show results
			}
			else if (turn == BLACK && backend.isLoser(black.size(), turn)) {
				// black loses, end game, show results
			}
		}
		
		if (placementCounter <= 0) {		// enter movement phase once all pieces have been initially placed
			isPlacementPhase = false;
		}
		*/

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
									if (backend.canRemove(black[i].getBoardRow(), black[i].getBoardCol(), BLACK)) {
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
									if (backend.canRemove(white[i].getBoardRow(), white[i].getBoardCol(), WHITE)) {
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
								/*
								if (!isRemovalPhase) {		// if removal phase, do not process as piece movement
									// TODO convert current GUI coordinates to backend board coordinates and
									// store in temp coordinates of piece -- white[i].setTempCoordinates(x, y)

									if (!backend.isvalidPosition(white[i].getTempRow(), white[i].getTempCol())) {
										// TODO reset piece coordinates
										break;
									}

									if (isPlacementPhase) {
										if (!backend.isValidPlacement(white[i].getTempRow(), white[i].getTempCol()) {
											// reset piece coordinates
											break;
										}
										else {
											// TODO update piece coordinates by passing the GUI coordinates to
											// white[i].setCoordinates(x, y)
											placementCounter--;
										}
									}
									else {
										if(!backend.isValidMove(white[i].getRow(), white[i].getCol(), white[i].getTempRow(), white[i].getTempCol(), white.size()) {
											//reset piece coordinates
											break;
										}
										else {
											// TODO update piece coordinates by passing the GUI coordinates to
											// white[i].setCoordinates(x, y)
										}
									}

									if (formsMill(white[i].getRow(), white[i].getCol(), WHITE) {
										removalPhase = true;
										backend.printBoard();
										break;
									}
									else {
										changeTurn(turn);
									}
								}
								*/
								backend.printBoard();		// print updated backend board for console logging
							}
						}
					}
					else if (turn == BLACK) {
						for (int i = 0; i < black.size(); i++) {
							if (black[i].pieceShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								selected = !selected;
								/*
								if (!isRemovalPhase) {		// if removal phase, do not process as piece movement
									// TODO convert current GUI coordinates to backend board coordinates and
									// store in temp coordinates of piece -- white[i].setTempCoordinates(x, y)

								if (!backend.isvalidPosition(white[i].getTempRow(), white[i].getTempCol())) {
									// TODO reset piece coordinates
									break;
								}

								if (isPlacementPhase) {
									if (!backend.isValidPlacement(white[i].getTempRow(), white[i].getTempCol(), black.size()) {
										// reset piece coordinates
										break;
									}
								else {
									// TODO update piece coordinates by passing the GUI coordinates to
									// white[i].setCoordinates(x, y)
									placementCounter--;
								}
								}
								else {
									if(!backend.isValidMove(white[i].getRow(), white[i].getCol(), white[i].getTempRow(), white[i].getTempCol()) {
										//reset piece coordinates
										break;
									}
									else {
										// TODO update piece coordinates by passing the GUI coordinates to
										// white[i].setCoordinates(x, y)
									}
								}

								if (formsMill(white[i].getRow(), white[i].getCol(), WHITE) {
									removalPhase = true;
									backend.printBoard();
									break;
								}
								else {
									changeTurn(turn);
								}
								}
								*/
								backend.printBoard();		// print updated backend board for console logging
							}
						}
					}
				}
				changeTurn(turn);		// delete line when logic functions are implemented, used for forcing turn change
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
		gameBoard.drawBoard(window);
		Piece::drawPieces(window, white);
		Piece::drawPieces(window, black);
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
}