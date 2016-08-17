#include "Tetris.h"

#include <algorithm>
#include <thread>
#include <cctype>
#include <memory>
#include <string>

using std::shared_ptr;
using std::make_shared;
using std::toupper;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::this_thread::sleep_for;
using std::to_string;
using std::max;
using namespace std::literals::chrono_literals;

milliseconds Tetris::operationTime() const {
    return milliseconds(650 - _level * 50);
}

bool Tetris::reachLeft() const {
    return _curr->left() == 0;
}

bool Tetris::reachRight() const {
    return _curr->right() == _board.width();
}

bool Tetris::reachBottom() const {
    return _curr->bottom() == _board.height();
}

void Tetris::stackBlock() {
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v)) _board.set(h, v);
    eliminateRows();
    notifyPaintBoard();
}

bool Tetris::rotate() {
    if (!canRotate()) return false;
    notifyEraseCurrentBlock();
    _curr->rotate();
    notifyPaintCurrentBlock();
    return true;
}

bool Tetris::canRotate() const {
    auto block = make_shared<Block>(*_curr);
    block->rotate();

    if (block->right() > _board.width() || block->bottom() > _board.height())
        return false;
    return !IsOverlap(_board, block);
}

bool Tetris::canShiftLeft() const {
    if (reachLeft())
        return false;
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v) && _board.at(h - 1, v))
                return false;
    return true;
}

bool Tetris::canShiftRight() const {
    if (reachRight())
        return false;
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v) && _board.at(h + 1, v))
                return false;
    return true;
}

bool Tetris::canShiftDown() const {
    if (reachBottom()) return false;
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v) && _board.at(h, v + 1))
                return false;
    return true;
}

bool Tetris::shiftDown() {
    if (!canShiftDown()) return false;
    notifyEraseCurrentBlock();
    _curr->shiftDown();
    notifyPaintCurrentBlock();
    return true;
}

bool Tetris::shiftLeft() {
    if (!canShiftLeft()) return false;
    notifyEraseCurrentBlock();
    _curr->shiftLeft();
    notifyPaintCurrentBlock();
    return true;
}

bool Tetris::shiftRight() {
    if (!canShiftRight()) return false;
    notifyEraseCurrentBlock();
    _curr->shiftRight();
    notifyPaintCurrentBlock();
    return true;
}

bool Tetris::IsOverlap(const Board& board, shared_ptr<Block> block) {
    for (int h = block->left(); h < block->right(); ++h)
        for (int v = block->top(); v < block->bottom(); ++v)
            if (block->at(h, v) && board.at(h, v))
                return true;
    return false;
}


bool Tetris::gameOver() const {
    return IsOverlap(_board, _curr);
}

void Tetris::reset() {
    _board.reset();
    notifyPaintBoard();

    _level = 1;
    _score = 0;
    _combo = 0;

    _next = Block::RandomBlock();
    AlignCenter(_previewBoard, *_next);
    notifyPaintNextBlock();

    _curr = Block::RandomBlock();
    AlignTopCenter(_board, *_curr);
    notifyPaintCurrentBlock();
}

void Tetris::eliminateRows() {
    auto rows = _board.eliminateRows();
    if (rows) {
        _score += compute_score(rows);
        if (_score > _level * _level * 1000)
            levelUp();
        ++_combo;
    } else
        _combo = 0;
    notifyUpdateGameInfo();
}

void Tetris::levelUp() {
    if (_level < MaxLevel)
        ++_level;
}

void Tetris::AlignHorizontalCenter(const Border& border, Block& block)
{
    block.setPosition((border.width() - block.width()) / 2, block.top());
}

void Tetris::AlignVerticalCenter(const Border& border, Block& block)
{
    block.setPosition(block.left(), (border.height() - block.height()) / 2);
}

void Tetris::AlignCenter(const Border& border, Block& block)
{
    AlignHorizontalCenter(border, block);
    AlignVerticalCenter(border, block);
}

void Tetris::AlignTopCenter(const Border& border, Block& block)
{
    block.setPosition(0, 0);
    AlignHorizontalCenter(border, block);
}

int Tetris::compute_score(int rows) const {
    return (rows + _combo) * rows * _board.width();
}

void Tetris::fetchNextBlock() {
    notifyEraseNextBlock();

    _curr = _next;
    _next = Block::RandomBlock();
    AlignCenter(_previewBoard, *_next);
    AlignTopCenter(_board, *_curr);

    notifyPaintNextBlock();
    notifyPaintCurrentBlock();
}

Tetris::Tetris(int row, int col, int previewBoardSize) 
    : _board(row, col), _previewBoard(previewBoardSize, previewBoardSize) { }

