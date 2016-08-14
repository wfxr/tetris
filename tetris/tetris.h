#pragma once

#include <thread>
#include <chrono>
#include <conio.h>
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
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::cout;
using std::endl;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

class Tetris {
public:
    Tetris(int row = 20, int col = 10);
    void run();
private:
    shared_ptr<Block> _curr;
    shared_ptr<Block> _next;

    Board _mainBoard;
    Position _mainBoardPos;
    Position _mainBoardTitlePos;
    const string _mainBoardTitle = "Tetris v1.0";

    Board _previewBoard;
    Position _previewBoardPos;
    Position _previewBoardTitlePos;
    const string _previewBoardTitle = "Next Block";

    const int MaxLevel = 10;
    const static string _blockBrush;
    const static string _borderBrush;
    const static string _eraseBrush;

    int _level = 1;
    int _score = 0;
    int _combo = 0;
    Position _speedPos;
    Position _scorePos;
    Position _comboPos;

    milliseconds operationTime() const;
    int score(int rows) const;
    string levelText() const;
    string scoreText() const;
    string comboText() const;

    bool gameOver() const;
    bool overlap() const;
    bool reachLeftBorder() const;
    bool reachRightBorder() const;
    bool reachBottomBorder() const;

    bool canRotate() const;
    bool canShiftLeft() const;
    bool canShiftRight() const;
    bool canShiftDown() const;

    bool rotate();
    bool shiftDown();
    bool shiftLeft();
    bool shiftRight();

    static int RealWidth(const Board& board);
    static int RealHeight(const Board& board);
    static bool IsOverlap(const Board& board, shared_ptr<Block> block);
    static void PaintBoard(const Board& board, Position pos);
    static void PaintBlock(const Board& board, Position boardPos, shared_ptr<Block> block, const string& brush);
    static void HorizontalCenterBlock(const Board& board, Block& block);
    static void VerticalCenterBlock(const Board& board, Block& block);
    static void PaintText(Position pos, const string& text);
    static Position TopCenterPosition(const Board& board, Position boardPos, int objectWidth);
    static Position BottomLeftPosition(const Board& board, Position boardPos);
    static Position BottomCenterPosition(const Board& board, Position boardPos, int objectWidth);

    void eraseCurrentBlock() const;
    void earseNextBlock() const;
    void paintCurrentBlock() const;
    void paintNextBlock() const;
    void paintMainBoard() const;
    void paintPreviewBoard() const;

    void eliminateBlocks();
    void levelUp();
    void readOpeartion();
    void TopCenterCurrentBlock();
    void centerNextBlock();
    void fetchNextBlock();
    void stackBlock();

    void showMainTitle() const ;
    void showPreviewBoardTitle() const;
    void showLevel() const;
    void showScore() const;
    void showCombo() const;
};
