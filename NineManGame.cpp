#include "NineManGame.h"
#include "BackendBoard.h"

void NineManGame::runWindow() {
	BackendBoard backend = BackendBoard();	// create object for backend logic handling
	window.create(sf::VideoMode(574, 574), "9 Men's Morris");

	window.setFramerateLimit(60);


	sf::CircleShape white1(20.f);
	white1.setFillColor(sf::Color::White);
	white1.setPosition(sf::Vector2f(360.f, 360.f));

	bool selected = false;				// track which piece is selected
	bool isPlacementPhase = true;		// track initial game phase
	bool removalPhase = false;			// track if a player can remove an opponent's piece
	int turn;							// track turn

	// set initial turn from player input (use WHITE/BLACK constants from class header file)

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//end loop when window closes
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//chnages origin of the moved dot to make dragging more intuitive on left click
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (turn == WHITE && white1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						white1.setOrigin(event.mouseButton.x - (white1.getPosition().x - white1.getOrigin().x),
							event.mouseButton.y - (white1.getPosition().y - white1.getOrigin().y));
						selected = !selected;
					}
					else if (turn == BLACK) { // handle black piece movement}
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (white1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						selected = !selected;		// stop dragging piece on mouse release
						/* Function calls:
							1. Check if valid position (adjust coordinates to closest position, convert to array ints to check)
								-If not, reset piece
							2. Check game phase
							3. If placement phase, check if valid placement (empty), decrement piece counter
							4. If movement phase, check if valid move (empty/adjacent)
								- If so, update piece class coordinates with valid pos.
							5. Check for a mill after step 3 or 4
							6. If mill, click to remove opponent piece (all non-mill pieces removed first)
							7. Check game ending conditions.
							8. If one is <3, declare winner, end game
							9. If one has no valid moves, end game
							10. Display game results
						*/


						/* valid move check
						// adjust current origin coordinates to nearest point, get respective backend coordinates
						// waiting on GUI to board coordinate translation

						if (!isPlacementPhase) {
							if (backend.isValidMove(white.getBoardRow(), white.getBoardCol(), NEWROW, NEWCOL)) {
								board[NEWROW][NEWCOL] = WHITE;
								board[white.getBoardRow()][white.getBoardCol()] = EMPTY;
								white.setCoordinates(NEWX, NEWY);
								white.setOrigin(NEWX, NEWY);
							}
							else {
								white.setOrigin(white.getX(), white.getY());  // reset piece to original position if invalid move
							}
						}
						*/

						/* mill check
						if (backend.formsMill(white.getBoardRow(), white.getBoardCol())) {
							removalPhase = true;
						} 
							don't change turn until removal complete - need to implement click to choose
							using canRemove() function
						*/ 

						backend.printBoard();		// print updated backend board for console logging
					}
				}
			}

			//moves the dot around when one has been selected
			if (selected) {
				white1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}
		window.clear();
		drawBoard("board.png");
		window.draw(bSprite);
		window.draw(white1);
		window.display();
	}
	return;
}

void NineManGame::drawBoard(std::string imageDirectory)
{
	if (!bTexture.loadFromFile(imageDirectory))
	{
		std::cerr << "Error\n";
	}
	bSprite.setTexture(bTexture);
	bSprite.setPosition(sf::Vector2f(12.f, 12.f));


}