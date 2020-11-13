#include "NineManGame.h"
#include "BackendBoard.h"


std::string NineManGame::getcolorString(int i) {
	if (i == WHITE) {
		return "White";
	}
	else { return "Black"; }
}

void NineManGame::runWindow() {
	
	BackendBoard backend = BackendBoard();	// create object for backend logic handling
	window.create(sf::VideoMode(720, 720), "9 Men's Morris");
	
	window.setFramerateLimit(60);


	/*sf::CircleShape white1(20.f);
	white1.setFillColor(sf::Color::White);
	white1.setPosition(sf::Vector2f(360.f, 360.f));*/
	//sf::RenderWindow window;
	bool selected = false;				// track which piece is selected
	bool isPlacementPhase = true;		// track initial game phase
	bool removalPhase = false;			// track if a player can remove an opponent's piece
	bool gameOver = false;				// track when game ends
	int turn ;							// track turn
	// set initial turn from player input (use WHITE/BLACK constants from class header file)
	turn = WHITE;
	Piece pc;
	NineManGame myGame("board.png", "theimage.ttf");

	//cout << " Toss a coin and enter the result:";
	//cin >> turn;	
	vector<sf::CircleShape> white, red, player(0);
	for (int i = 0; i < 18; i = i + 2)
	{
		red.push_back(pc.pcs(15.f, (i + 1) * 20, 17, sf::Color::Red));
		white.push_back(pc.pcs(15.f, (i + 1) * 20, 50, sf::Color::Yellow));
	}
	(turn == WHITE ? player = white : player = red);
	
	int n = 0;
	// set initial turn from player input (use WHITE/BLACK constants from class header file)
	//turn = WHITE;

	while (window.isOpen())
	{
		/* Game over check, need piece vectors to get piece count
		if (turn == WHITE && isLoser(WHITEVECTOR.SIZE(), turn)) {
			// white loses, end game, show results
		}
		else if (turn == BLACK && isLoser(BLACKVECTOR.SIZE(), turn)) {
			// black loses, end game, show results
		}
		*/

		sf::Event event;
		while (window.pollEvent(event))
		{
			//end loop when window closes
			if (event.type == sf::Event::Closed) 
				window.close();
			
			//chnages origin of the moved dot to make dragging more intuitive on left click
			 if (event.type == sf::Event::MouseButtonPressed) 
				if (event.mouseButton.button == sf::Mouse::Left) 
					for (int i = 0; i < player.size(); i++) {
						if ( player[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							selected = true; n = i;
							player[i].setOrigin(event.mouseButton.x - (player[i].getPosition().x - player[i].getOrigin().x),
								event.mouseButton.y - (player[i].getPosition().y - player[i].getOrigin().y));

						}
					}
					//else if (turn == BLACK) {} // handle black piece movement}

				
				 if (event.type == sf::Event::MouseButtonReleased)
					if (event.mouseButton.button == sf::Mouse::Left) {
						selected = false;
					}
				/*
				if (player[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					selected = !selected;		// stop dragging piece on mouse release
					 Function calls:
						1. Check if valid position (adjust coordinates to closest position, convert to array ints to check)
							-If not, reset piece
						2. Check game phase
						3. If placement phase, check if valid placement (empty), decrement piece counter
						4. If movement phase, check if valid move (empty/adjacent)
							- If so, update piece class coordinates with valid pos.
						5. Check for a mill after step 3 or 4
						6. If mill, click to remove opponent piece (all non-mill pieces removed first)
						7. Check game ending conditions.
						8. If one is <3, declare winner, end game (checked at beginning of loop)
						9. If one has no valid moves, end game (checked at beginning of loop)
						10. Display game results



					 valid move check
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


					 mill check
					if (backend.formsMill(white.getBoardRow(), white.getBoardCol())) {
						removalPhase = true;
					}
						don't change turn until removal complete - need to implement click to choose
						using canRemove() function

					backend.printBoard();		// print updated backend board for console logging

				}
*/


			

			//moves the dot around when one has been selected
			if (selected) {
				player[n].setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}
		window.clear();
		//drawBoard("board.png");
		//window.draw(bSprite);
		myGame.drawBoard(window);
		pc.drawDots(window, player);
		(turn == WHITE ? pc.drawDots(window, red) : pc.drawDots(window, white));		
		//window.draw(white1);
		window.display();
	}
	return;
}
NineManGame::NineManGame(string imageDIrectory, string image) //upload an image from file and the font 
{
	if (!bTexture.loadFromFile(imageDIrectory))
	{
		cerr << "Error\n";
	}
	bSprite.setTexture(bTexture);
	bSprite.setPosition(sf::Vector2f(85.f, 85.f));
	if (!font.loadFromFile(image))
	{
		cerr << "Error\n";
	}

	for (int i = 0; i < 7; i++) {
		text1[i].setFont(font);
		text1[i].setString(h[i]);
		text1[i].setPosition((83 * i) + 108, 600);
		text2[i].setFont(font);
		text2[i].setString(v[i]);
		text2[i].setPosition(85, (83 * i) + 90);
	}

}
void NineManGame::drawBoard(sf::RenderWindow& window)
{
	window.draw(bSprite);
	for (int i = 0; i < 7; i++)
	{
		window.draw(text1[i]);
		window.draw(text2[i]);
	}

}