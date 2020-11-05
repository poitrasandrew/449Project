#include "stdafx.h"
#include "CppUnitTest.h"
#include <SFML/Graphics.hpp>
#include "../449Project-master/BackendBoard.h"
#include "../449Project-master/BackendBoard.cpp"
#include "../449Project-master/Piece.h"
#include "../449Project-master/NineManGame.h"

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
}