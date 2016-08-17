#include "ConsoleTetris.h"
#include "ConsoleUtility.h"

#include <iostream>
#include <chrono>
#include <thread>

using std::string;
using std::cout;
using std::make_shared;
using std::shared_ptr;
using std::chrono::system_clock;
using std::this_thread::sleep_for;
using std::to_string;
using namespace std::literals::chrono_literals;


const string ConsoleTetris::_blockBrush("¨~");
const string ConsoleTetris::_eraseBrush("¡¡");
const string ConsoleTetris::_borderBrush("¡õ");

void ConsoleTetris::run() {
    CursorHide();
    ClearScreen();
    printTitle();
    PaintBorder(_game.getMainBoard(), _mainBoardPos);
    PaintBorder(_game.getPreviewBoard(), _previewBoardPos);
    updateGameInfo();

    _game.subscribe(shared_from_this());
    _game.reset();

    while (!_game.gameOver()) {
        do {
            readOperation();
            if (_quit) {
                ClearScreen();
                return;
            }
        } while (_game.shiftDown());
        _game.stackBlock();
        _game.fetchNextBlock();
    }

    ClearScreen();
    CursorShow();
}

void ConsoleTetris::paintCurrentBlock() {
    PaintBlock(_mainBoardPos, _game.currentBlock(), _blockBrush);
}

void ConsoleTetris::paintNextBlock() {
    PaintBlock(_previewBoardPos, _game.nextBlock(), _blockBrush);

}

void ConsoleTetris::eraseCurrentBlock() {
    PaintBlock(_mainBoardPos, _game.currentBlock(), _eraseBrush);
}

void ConsoleTetris::eraseNextBlock() {
    PaintBlock(_previewBoardPos, _game.nextBlock(), _eraseBrush);
}

void ConsoleTetris::updateBoard() {
    PaintBoard(_game.getMainBoard(), _mainBoardPos);
}

ConsoleTetris::ConsoleTetris(int rows, int cols, int previewBoardSize) : _game(rows, cols, previewBoardSize) {
    Position pos{4, 4};
    _mainBoardPos = pos;

    pos.X += RealWidth(_game.getMainBoard()) + 2;
    _previewBoardPos = pos;

    pos.X += 3;
    pos.Y += RealHeight(_game.getPreviewBoard()) + 2;
    _statusPos = pos;
}

void ConsoleTetris::PaintBorder(const Board& board, struct Position pos) {
    CursorGoto(pos);
    for (int x = 0; x < board.width() + 2; ++x)
        cout << _borderBrush;
    ++pos.Y;

    for (int y = 0; y < board.height(); ++y , ++pos.Y) {
        CursorGoto(pos);
        cout << _borderBrush;
        for (int x = 0; x < board.width(); ++x)
            cout << _eraseBrush;
        cout << _borderBrush;
    }

    CursorGoto(pos);
    for (int x = 0; x < board.width() + 2; ++x)
        cout << _borderBrush;
}

void ConsoleTetris::PaintBoard(const Board& board, Position pos) {
    pos.Y += 1;
    pos.X += 2;

    for (int y = 0; y < board.height(); ++y , ++pos.Y) {
        CursorGoto(pos);
        for (int x = 0; x < board.width(); ++x)
            cout << (board.at(x, y) ? _blockBrush : _eraseBrush);
    }
}

shared_ptr<ConsoleTetris> ConsoleTetris::Create(int rows, int cols) {
    return shared_ptr<ConsoleTetris>(new ConsoleTetris(rows, cols));
}

void ConsoleTetris::PaintBlock(Position boardPos, shared_ptr<Block> block, const string& brush) {
    auto blockPos = boardPos;
    blockPos.X += 2 + block->left() * 2;
    blockPos.Y += 1 + block->top();

    for (int v = block->top(); v < block->bottom(); ++v , ++blockPos.Y) {
        CursorGoto(blockPos);
        for (int h = block->left(); h < block->right(); ++h) {
            if (block->at(h, v))
                cout << brush;
            else
                CursorRight(2);
        }
    }
}

void ConsoleTetris::readOperation() {
    auto time = system_clock::now();
    while (system_clock::now() - time < _game.operationTime()) {
        if (_kbhit()) {
            switch (getch()) {
                case KEY_UP:
                case 'w':
                case 'k':
                    _game.rotate();
                    break;
                case KEY_DOWN:
                case 's':
                case 'j':
                    while (_game.shiftDown())
                        sleep_for(10ms);
                    if (_game.canShiftLeft() || _game.canShiftDown())
                        readOperation();
                    return;
                case KEY_LEFT:
                case 'a':
                case 'h':
                    _game.shiftLeft();
                    break;
                case KEY_RIGHT:
                case 'd':
                case 'l':
                    _game.shiftRight();
                    break;
                case 'q':
                    _game.unsubscribe(shared_from_this());
                    _quit = true;
                    return;
                case 'p':
                    while (getch() != 'p')
                        break;
                default:
                    break;
            }
        }
        sleep_for(_game.operationTime() / 10);
    }
}

void ConsoleTetris::printTitle() const {
    static string title{"Tetris v1.0"};
    auto pos = _mainBoardPos;
    pos.X += (_game.getMainBoard().width() * 2 + 4 - title.length()) / 2;
    pos.Y -= 2;
    CursorGoto(pos);
    cout << title;
}

void ConsoleTetris::AlignHorizontalCenter(const Border& border, Position& position, int width) {
    position.X = (border.width() - width) / 2;
}

string ConsoleTetris::levelText() const {
    return "LEVEL: " + to_string(_game.level());
}

string ConsoleTetris::scoreText() const {
    return "SCORE: " + to_string(_game.score());
}

string ConsoleTetris::comboText() const {
    return "COMBO: " + to_string(_game.combo());
}

void ConsoleTetris::updateGameInfo() {
    auto pos = _statusPos;
    CursorGoto(pos);
    cout << scoreText();

    pos.Y += 2;
    CursorGoto(pos);
    cout << levelText();

    pos.Y += 2;
    CursorGoto(pos);
    cout << comboText();

    pos.Y += 3;
    CursorGoto(pos);
    cout << "PAUSE: <P>";

    pos.Y += 2;
    CursorGoto(pos);
    cout << " QUIT: <Q>";
}

