#include "stdafx.h"
#include "CppUnitTest.h"
#include <SFML/Graphics.hpp>
#include "../449Project-master/BackendBoard.h"
#include "../449Project-master/BackendBoard.cpp"
#include "../449Project-master/Piece.h"
#include "../449Project-master/Piece.cpp"
#include "../449Project-master/Board.h"
#include "../449Project-master/Board.cpp"
#include "../449Project-master/NineManGame.h"
#include "../449Project-master/NineManGame.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(millTests)
	{
	public:
		BackendBoard backend;
		TEST_METHOD_INITIALIZE(setUp)
		{
			backend = BackendBoard();
		}
		
		TEST_METHOD(HorizMillTestL)
		{
			// test horizontal mill with piece on left side of mill
			backend.updateBoard(0, 0, NineManGame::WHITE);
			backend.updateBoard(0, 3, NineManGame::WHITE);
			backend.updateBoard(0, 6, NineManGame::WHITE);
			Assert::IsTrue(backend.formsMill(0, 0, NineManGame::WHITE));
		}

		TEST_METHOD(HorizMillTestM)
		{
			// test horizontal mill with piece in middle of mill
			backend.updateBoard(4, 2, NineManGame::WHITE);
			backend.updateBoard(4, 3, NineManGame::WHITE);
			backend.updateBoard(4, 4, NineManGame::WHITE);
			Assert::IsTrue(backend.formsMill(4, 3, NineManGame::WHITE));
		}

		TEST_METHOD(HorizMillTestR)
		{
			// test horizontal mill with piece on right side of mill
			backend.updateBoard(3, 4, NineManGame::BLACK);
			backend.updateBoard(3, 5, NineManGame::BLACK);
			backend.updateBoard(3, 6, NineManGame::BLACK);
			Assert::IsTrue(backend.formsMill(3, 6, NineManGame::BLACK));
		}

		TEST_METHOD(HorizMillTestMid)
		{
			// test horizontal mill across middle point
			backend.updateBoard(3, 1, NineManGame::WHITE);
			backend.updateBoard(3, 2, NineManGame::WHITE);
			backend.updateBoard(3, 4, NineManGame::WHITE);
			Assert::IsFalse(backend.formsMill(3, 4, NineManGame::WHITE));
		}

		TEST_METHOD(HorizMillTestLow)
		{
			// test horizontal mill with less than 3 pieces
			backend.updateBoard(6, 3, NineManGame::WHITE);
			backend.updateBoard(6, 6, NineManGame::WHITE);
			Assert::IsFalse(backend.formsMill(6, 3, NineManGame::WHITE));
		}

		TEST_METHOD(HorizMillTestOpp)
		{
			// test horizontal mill with opponent in it
			backend.updateBoard(5, 1, NineManGame::WHITE);
			backend.updateBoard(5, 3, NineManGame::WHITE);
			backend.updateBoard(5, 5, NineManGame::BLACK);
			Assert::IsFalse(backend.formsMill(5, 3, NineManGame::WHITE));
		}

		TEST_METHOD(VertMillTestT)
		{
			// test vertical mill with piece at top of mill
			backend.updateBoard(0, 0, NineManGame::WHITE);
			backend.updateBoard(3, 0, NineManGame::WHITE);
			backend.updateBoard(6, 0, NineManGame::WHITE);
			Assert::IsTrue(backend.formsMill(0, 0, NineManGame::WHITE));
		}

		TEST_METHOD(VertMillTestM)
		{
			// test vertical mill with piece in middle of mill
			backend.updateBoard(1, 5, NineManGame::WHITE);
			backend.updateBoard(3, 5, NineManGame::WHITE);
			backend.updateBoard(5, 5, NineManGame::WHITE);
			Assert::IsTrue(backend.formsMill(3, 5, NineManGame::WHITE));
		}

		TEST_METHOD(VertMillTestB)
		{
			// test vertical mill with piece at the bottom of mill
			backend.updateBoard(4, 3, NineManGame::WHITE);
			backend.updateBoard(5, 3, NineManGame::WHITE);
			backend.updateBoard(6, 3, NineManGame::WHITE);
			Assert::IsTrue(backend.formsMill(6, 3, NineManGame::WHITE));
		}

		TEST_METHOD(VertMillTestMid)
		{
			// test vertical mill across middle point
			backend.updateBoard(0, 3, NineManGame::BLACK);
			backend.updateBoard(1, 3, NineManGame::BLACK);
			backend.updateBoard(6, 3, NineManGame::BLACK);
			Assert::IsFalse(backend.formsMill(1, 3, NineManGame::BLACK));
		}

		TEST_METHOD(VertMillTestLow)
		{
			// test vertical mill with less than 3 pieces
			backend.updateBoard(0, 6, NineManGame::BLACK);
			backend.updateBoard(3, 6, NineManGame::BLACK);
			Assert::IsFalse(backend.formsMill(0, 6, NineManGame::BLACK));
		}

		TEST_METHOD(VertMillTestOpp)
		{
			// test vertical mill with opponent in it
			backend.updateBoard(2, 2, NineManGame::BLACK);
			backend.updateBoard(3, 2, NineManGame::WHITE);
			backend.updateBoard(4, 2, NineManGame::BLACK);
			Assert::IsFalse(backend.formsMill(2, 2, NineManGame::BLACK));
		}

	};

	TEST_CLASS(validPositionTests)
	{
	public:
		BackendBoard backend;
		TEST_METHOD_INITIALIZE(setUp)
		{
			backend = BackendBoard();
		}

		TEST_METHOD(invalidPosTest1)
		{
			Assert::IsFalse(backend.isvalidPosition(1, 0));
		}

		TEST_METHOD(invalidPosTest2)
		{
			Assert::IsFalse(backend.isvalidPosition(4, 1));
		}

		TEST_METHOD(invalidPosTest3)
		{
			Assert::IsFalse(backend.isvalidPosition(3, 3));
		}

		TEST_METHOD(ValidPosTest1)
		{
			Assert::IsTrue(backend.isvalidPosition(0, 0));
		}

		TEST_METHOD(ValidPosTest2)
		{
			Assert::IsTrue(backend.isvalidPosition(6, 6));
		}

		TEST_METHOD(ValidPosTest3)
		{
			Assert::IsTrue(backend.isvalidPosition(3, 4));
		}

		TEST_METHOD(ValidPosTest4)
		{
			Assert::IsTrue(backend.isvalidPosition(2, 4));
		}

		TEST_METHOD(ValidPosTest5)
		{
			Assert::IsTrue(backend.isvalidPosition(1, 5));
		}
	};

	TEST_CLASS(validPlacementTests)
	{
	public:
		BackendBoard backend;
		TEST_METHOD_INITIALIZE(setUp)
		{
			backend = BackendBoard();
		}

		TEST_METHOD(EmptyTest1)
		{
			Assert::IsTrue(backend.isvalidPlacement(0, 0));
		}

		TEST_METHOD(EmptyTest2)
		{
			Assert::IsTrue(backend.isvalidPlacement(1, 3));
		}

		TEST_METHOD(NonEmptyTest1)
		{
			backend.updateBoard(3, 1, NineManGame::WHITE);
			Assert::IsFalse(backend.isvalidPlacement(3, 1));
		}

		TEST_METHOD(NonEmptyTest2)
		{
			backend.updateBoard(6, 5, NineManGame::BLACK);
			Assert::IsFalse(backend.isvalidPlacement(6, 5));
		}
	};

	TEST_CLASS(validMoveTests)
	{
	public:
		BackendBoard backend;
		TEST_METHOD_INITIALIZE(setUp)
		{
			backend = BackendBoard();
		}

		TEST_METHOD(HorizMoveLeft)
		{
			// test horizontal move to left empty, adjacent point
			Assert::IsTrue(backend.isValidMove(0, 3, 0, 0));
		}

		TEST_METHOD(HorizMoveRight)
		{
			// test horizontal move to right empty, adjacent point
			Assert::IsTrue(backend.isValidMove(1, 1, 1, 3));
		}

		TEST_METHOD(HorizMoveNonAdj)
		{
			// test horizontal move to a nonadjacent empty point
			Assert::IsFalse(backend.isValidMove(5, 1, 5, 6));
		}

		TEST_METHOD(HorizMoveNonEmpty)
		{
			// test horizontal move to a non-empty, adjacent point
			backend.updateBoard(4, 3, NineManGame::WHITE);
			Assert::IsFalse(backend.isValidMove(4, 4, 4, 3));
		}

		TEST_METHOD(VertMoveUp)
		{
			// test vertical move to empty, adjacent upper point
			Assert::IsTrue(backend.isValidMove(3, 0, 0, 0));
		}

		TEST_METHOD(VertMoveDown)
		{
			// test vertical move to empty, adjacent lower point
			Assert::IsTrue(backend.isValidMove(4, 3, 5, 3));
		}

		TEST_METHOD(VertMoveNonAdj)
		{
			// test vertical move to a nonadjacent, empty point
			Assert::IsFalse(backend.isValidMove(1, 5, 5, 5));
		}

		TEST_METHOD(VertMoveNonEmpty)
		{
			// test vertical move to a nonadjacent, empty point
			backend.updateBoard(3, 6, NineManGame::BLACK);
			Assert::IsFalse(backend.isValidMove(6, 6, 3, 6));
		}

		TEST_METHOD(DiagMove)
		{
			// test diagonal move
			Assert::IsFalse(backend.isValidMove(1, 5, 2, 4));
		}
	};

	TEST_CLASS(isLoserTests)
	{
		// single piece test methods assume other pieces on board are blocked as well
		// assumes piece count given by caller method
		// method should return false if a valid move is not available (player is not a loser)
	public:
		BackendBoard backend;
		TEST_METHOD_INITIALIZE(setUp)
		{
			backend = BackendBoard();
		}

		TEST_METHOD(LoserTestU)
		{
			// test if player is loser when there is an valid move above a piece
			backend.updateBoard(3, 0, NineManGame::WHITE);
			backend.updateBoard(6, 0, NineManGame::BLACK);
			backend.updateBoard(3, 1, NineManGame::BLACK);
			Assert::IsFalse(backend.isLoser(4, NineManGame::WHITE));
		}
		TEST_METHOD(LoserTestB)
		{
			// test if player is loser when there is an valid move below a piece
			backend.updateBoard(1, 5, NineManGame::WHITE);
			backend.updateBoard(1, 3, NineManGame::BLACK);
			Assert::IsFalse(backend.isLoser(6, NineManGame::WHITE));
		}
		TEST_METHOD(LoserTestL)
		{
			// test if player is loser when there is an valid move to the left of a piece
			backend.updateBoard(5, 3, NineManGame::BLACK);
			backend.updateBoard(4, 3, NineManGame::WHITE);
			backend.updateBoard(6, 3, NineManGame::WHITE);
			backend.updateBoard(5, 5, NineManGame::WHITE);
			Assert::IsFalse(backend.isLoser(5, NineManGame::BLACK));
		}
		TEST_METHOD(LoserTestR)
		{
			// test if player is loser when there is an valid move to the right of a piece
			backend.updateBoard(1, 3, NineManGame::BLACK);
			backend.updateBoard(1, 1, NineManGame::WHITE);
			backend.updateBoard(2, 3, NineManGame::WHITE);
			backend.updateBoard(0, 3, NineManGame::WHITE);
			Assert::IsFalse(backend.isLoser(7, NineManGame::BLACK));
		}
		TEST_METHOD(LoserTestNone)
		{
			// test if player is loser when there are no valid moves for a piece
			backend.updateBoard(4, 3, NineManGame::WHITE);
			backend.updateBoard(4, 2, NineManGame::BLACK);
			backend.updateBoard(4, 4, NineManGame::BLACK);
			backend.updateBoard(5, 3, NineManGame::BLACK);
			Assert::IsTrue(backend.isLoser(8, NineManGame::WHITE));
		}
		TEST_METHOD(LoserTestSet1)
		{
			// test if player is loser when there are no valid moves for a set of pieces
			backend.updateBoard(6, 0, NineManGame::BLACK);
			backend.updateBoard(2, 4, NineManGame::BLACK);
			backend.updateBoard(3, 4, NineManGame::BLACK);
			backend.updateBoard(5, 3, NineManGame::BLACK);

			backend.updateBoard(6, 3, NineManGame::WHITE);
			backend.updateBoard(3, 0, NineManGame::WHITE);
			backend.updateBoard(2, 3, NineManGame::WHITE);
			backend.updateBoard(3, 5, NineManGame::WHITE);
			backend.updateBoard(4, 4, NineManGame::WHITE);
			backend.updateBoard(5, 1, NineManGame::WHITE);
			backend.updateBoard(4, 3, NineManGame::WHITE);
			backend.updateBoard(5, 5, NineManGame::WHITE);

			Assert::IsTrue(backend.isLoser(4, NineManGame::BLACK));
		}
		TEST_METHOD(LoserTestSet2)
		{
			// test if player is loser when there is a valid move for at least one of their pieces
			backend.updateBoard(1, 3, NineManGame::WHITE);
			backend.updateBoard(0, 6, NineManGame::WHITE);
			backend.updateBoard(3, 6, NineManGame::WHITE);
			backend.updateBoard(6, 3, NineManGame::WHITE);
			backend.updateBoard(6, 6, NineManGame::WHITE);

			backend.updateBoard(0, 3, NineManGame::BLACK);
			backend.updateBoard(2, 3, NineManGame::BLACK);
			backend.updateBoard(1, 1, NineManGame::BLACK);
			backend.updateBoard(5, 1, NineManGame::BLACK);
			backend.updateBoard(3, 5, NineManGame::BLACK);


			Assert::IsFalse(backend.isLoser(5, NineManGame::WHITE));
		}
		TEST_METHOD(LoserTestLow)
		{
			// test if player is loser when they have less than three pieces on the board
			Assert::IsTrue(backend.isLoser(2, NineManGame::WHITE));
		}
		TEST_METHOD(LoserTestFly)
		{
			// test if player is loser when they have the ability to fly
			Assert::IsFalse(backend.isLoser(3, NineManGame::BLACK));
		}
	};

	TEST_CLASS(removalTests)
	{
	public:
		BackendBoard backend;
		TEST_METHOD_INITIALIZE(setUp)
		{
			backend = BackendBoard();
		}

		TEST_METHOD(RemovalTest1)
		{
			// test if a piece in a mill can be removed when there is another piece not in a mill
			backend.updateBoard(0, 0, NineManGame::WHITE);
			backend.updateBoard(0, 3, NineManGame::WHITE);
			backend.updateBoard(0, 6, NineManGame::WHITE);
			backend.updateBoard(2, 2, NineManGame::WHITE);
			Assert::IsFalse(backend.canRemove(0, 0, NineManGame::WHITE));
		}

		TEST_METHOD(RemovalTest2)
		{
			// test if a piece in a mill can be removed when all other pieces are in a mill as well
			backend.updateBoard(3, 1, NineManGame::BLACK);
			backend.updateBoard(1, 1, NineManGame::BLACK);
			backend.updateBoard(5, 1, NineManGame::BLACK);
			Assert::IsTrue(backend.canRemove(3, 1, NineManGame::BLACK));
		}

	};
}