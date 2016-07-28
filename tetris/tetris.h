#pragma once

#include <thread>
#include <chrono>
#include <conio.h>
#include <random>
#include <cctype>
#include <memory>
#include <iostream>
#include <thread>
#include <string>

#include "Block.h"
#include "Board.h"
#include "Position.h"

using std::string;
using std::this_thread::sleep_for;
using std::shared_ptr;
using std::make_shared;
using std::toupper;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::cout;
using std::endl;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

class Tetris {
private:
	Board _mainBoard;
	Board _previewBoard;
	shared_ptr<Block> _curr;
	shared_ptr<Block> _next;
	Position _mainBoardPos;
	Position _previewBoardPos;
	int speed = 2;
	static const int BlockShapesCount = static_cast<int>(ShapeCategory::Count);

	milliseconds operationTime();
	bool isOverlap() const;
	bool isOverlap(shared_ptr<Block> block) const;

	bool reachLeftBorder() const;
	bool reachRightBorder() const;
	bool reachBottomBorder() const;

	void stackBlock();
	bool canRotate();
	bool canShiftLeft();
	bool canShiftRight();
	bool canShiftDown();

	bool rotate();
	bool shiftDown();
	bool shiftLeft();
	bool shiftRight();

	static void paintBoard(const Board& board, Position pos = Position(), const string& brush = "¨~");
	static void paintBlock(const Board& board, Position boardPos, shared_ptr<Block> block, const string& brush = "¨~");
	static int realWidth(const Board& board);
	static void HorizontalCenterBlock(const Board& board, Position boardPos, Block& block);
	static void VerticalCenterBlock(const Board& board, Position boardPos, Block& block);

	void eraseCurrentBlock();
	void paintCurrentBlock(const string& brush="¨~");

	void paintNextBlock(const string& brush = "¨~");
	void earseNextBlock();

	void paintMainBoard();
	void paintPreviewBoard();


	shared_ptr<Block> randomBlock();
	void readOpeartion();
	bool gameOver();
	int eliminateBlocks();

	void TopCenterCurrentBlock();
	void centerNextBlock();
	void fetchNextBlock();
public:
	Tetris(int row = 20, int col = 10);

	void run() {
		paintMainBoard();
		paintPreviewBoard();
		fetchNextBlock();
		paintCurrentBlock();
		paintNextBlock();

		do {
			do {
				readOpeartion();
			} while (shiftDown());
			stackBlock();
			eliminateBlocks();
			fetchNextBlock();
			paintCurrentBlock();
			paintNextBlock();
		} while (!gameOver());
		paintCurrentBlock();
	}
};