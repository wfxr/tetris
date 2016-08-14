#include "Tetris.h"
#include "ConsoleUtility.h"

#include <algorithm>

using std::to_string;
using std::max;

const string Tetris::_blockBrush("▇");
const string Tetris::_eraseBrush("　");
const string Tetris::_borderBrush("□");

milliseconds Tetris::operationTime() const {
    return milliseconds(650 - _level * 50);
}

bool Tetris::overlap() const {
    return IsOverlap(_mainBoard, _curr);
}

bool Tetris::reachLeftBorder() const {
    return _curr->left() == 0;
}

bool Tetris::reachRightBorder() const {
    return _curr->right() == _mainBoard.width();
}

bool Tetris::reachBottomBorder() const {
    return _curr->bottom() == _mainBoard.height();
}

void Tetris::stackBlock() {
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v)) _mainBoard.set(h, v);
    eliminateBlocks();
}

void Tetris::showMainTitle() const {
    CursorGoto(_mainBoardTitlePos);
    cout << _mainBoardTitle << endl;
    paintPreviewBoard();
}

void Tetris::showPreviewBoardTitle() const {
    CursorGoto(_previewBoardTitlePos);
    cout << _previewBoardTitle << endl;
    paintPreviewBoard();
}

void Tetris::showScore() const {
    CursorGoto(_scorePos);
    cout << scoreText();
}


void Tetris::showLevel() const {
    CursorGoto(_speedPos);
    cout << levelText();
}

void Tetris::showCombo() const {
    CursorGoto(_comboPos);
    cout << comboText();
}

bool Tetris::rotate() {
    if (!canRotate()) return false;

    eraseCurrentBlock();
    _curr->rotate();
    paintCurrentBlock();
    return true;
}

bool Tetris::canRotate() const {
    auto block = make_shared<Block>(*_curr);
    block->rotate();

    auto br = block->right();
    auto bb = block->bottom();
    if (block->right() > _mainBoard.width() || block->bottom() > _mainBoard.height())
        return false;
    return !IsOverlap(_mainBoard, block);
}

bool Tetris::canShiftLeft() const {
    if (reachLeftBorder())
        return false;
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v) && _mainBoard.at(h - 1, v))
                return false;
    return true;
}

bool Tetris::canShiftRight() const {
    if (reachRightBorder())
        return false;
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v) && _mainBoard.at(h + 1, v))
                return false;
    return true;
}

bool Tetris::canShiftDown() const {
    if (reachBottomBorder())
        return false;
    for (int h = _curr->left(); h < _curr->right(); ++h)
        for (int v = _curr->top(); v < _curr->bottom(); ++v)
            if (_curr->at(h, v) && _mainBoard.at(h, v + 1))
                return false;
    return true;
}

bool Tetris::shiftDown() {
    if (!canShiftDown()) return false;

    eraseCurrentBlock();
    _curr->shiftDown();
    paintCurrentBlock();
    return true;
}

bool Tetris::shiftLeft() {
    if (!canShiftLeft()) return false;

    eraseCurrentBlock();
    _curr->shiftLeft();
    paintCurrentBlock();
    return true;
}

bool Tetris::shiftRight() {
    if (!canShiftRight()) return false;

    eraseCurrentBlock();
    _curr->shiftRight();
    paintCurrentBlock();
    return true;
}

bool Tetris::IsOverlap(const Board& board, shared_ptr<Block> block) {
    for (int h = block->left(); h < block->right(); ++h)
        for (int v = block->top(); v < block->bottom(); ++v)
            if (block->at(h, v) && board.at(h, v))
                return true;
    return false;
}

void Tetris::PaintBoard(const Board& board, Position pos) {
    CursorGoto(pos);
    for (int x = 0; x < board.width() + board.thickness() * 2; ++x)
        cout << _borderBrush;
    ++pos.Y;

    for (int y = 0; y < board.height(); ++y , ++pos.Y) {
        CursorGoto(pos);
        cout << _borderBrush;
        for (int x = 0; x < board.width(); ++x)
            if (board.at(x, y))
                cout << _blockBrush;
            else
                cout << "  ";
        cout << _borderBrush;
    }

    CursorGoto(pos);
    for (int x = 0; x < board.width() + board.thickness() * 2; ++x)
        cout << _borderBrush;
}

void Tetris::PaintBlock(const Board& board, Position boardPos, shared_ptr<Block> block, const string& brush) {
    auto blockPos = boardPos;
    blockPos.X += board.thickness() * 2 + block->left() * 2;
    blockPos.Y += board.thickness() + block->top();

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

int Tetris::RealWidth(const Board& board) {
    return board.thickness() * 2 + board.width() * 2;
}

int Tetris::RealHeight(const Board& board) {
    return board.thickness() * 2 + board.height();
}

Position Tetris::BottomCenterPosition(const Board& board, Position boardPos, int objectWidth) {
    return Position{
        boardPos.X + (RealWidth(board) - objectWidth) / 2,
        boardPos.Y + (RealHeight(board))
    };
}

void Tetris::paintCurrentBlock() const {
    PaintBlock(_mainBoard, _mainBoardPos, _curr, _blockBrush);
}

void Tetris::eraseCurrentBlock() const {
    PaintBlock(_mainBoard, _mainBoardPos, _curr, _eraseBrush);
}

void Tetris::paintNextBlock() const {
    PaintBlock(_previewBoard, _previewBoardPos, _next, _blockBrush);
}

void Tetris::earseNextBlock() const {
    PaintBlock(_previewBoard, _previewBoardPos, _next, _eraseBrush);
}

void Tetris::paintMainBoard() const {
    PaintBoard(_mainBoard, _mainBoardPos);
}

void Tetris::paintPreviewBoard() const {
    PaintBoard(_previewBoard, _previewBoardPos);
}

void Tetris::readOpeartion() {
    auto time = system_clock::now();
    while (system_clock::now() - time < operationTime()) {
        if (_kbhit()) {
            switch (toupper(_getch())) {
                case 'S':
                    while (shiftDown())
                        sleep_for(10ms);
                    if (canShiftLeft() || canShiftRight())
                        readOpeartion();
                    return;
                case 'A':
                    shiftLeft();
                    break;
                case 'D':
                    shiftRight();
                    break;
                case 'W':
                    rotate();
                    break;
                default:
                    break;
            }
        }
        sleep_for(operationTime() / 10);
    }
}

bool Tetris::gameOver() const {
    return overlap();
}

void Tetris::eliminateBlocks() {
    auto rows = _mainBoard.eliminateRows();
    if (rows) {
        ++_combo;
        _score += score(rows);
        if (_score > _level * _level * 1000) {
            levelUp();
            showLevel();
        }
        showScore();
        paintMainBoard();
    } else
        _combo = 0;
    showCombo();
}

void Tetris::levelUp() {
    if (_level < MaxLevel)
        ++_level;
}

void Tetris::HorizontalCenterBlock(const Board& board, Block& block) {
    block.setPosition((board.width() - block.width()) / 2, block.top());
}

void Tetris::VerticalCenterBlock(const Board& board, Block& block) {
    block.setPosition(block.left(), (board.height() - block.height()) / 2);
}

void Tetris::PaintText(Position pos, const string& text) {
    CursorGoto(pos);
    cout << text;
}

Position Tetris::TopCenterPosition(const Board& board, Position boardPos, int objectWidth) {
    return Position{
        boardPos.X + (RealWidth(board) - objectWidth) / 2,
        boardPos.Y
    };
}

Position Tetris::BottomLeftPosition(const Board& board, Position boardPos) {
    return Position{
        boardPos.X,
        boardPos.Y + (RealHeight(board))
    };
}

int Tetris::score(int rows) const {
    return rows * rows * 10 + rows * (1 + _combo) * 10;
}

string Tetris::levelText() const {
    return "LEVEL: " + to_string(_level);
}

string Tetris::scoreText() const {
    return "SCORE: " + to_string(_score);
}

string Tetris::comboText() const {
    return "COMBO: " + to_string(_combo);
}

void Tetris::TopCenterCurrentBlock() {
    _curr->setPosition(0, 0);
    HorizontalCenterBlock(_mainBoard, *_curr);
}

void Tetris::centerNextBlock() {
    HorizontalCenterBlock(_previewBoard, *_next);
    VerticalCenterBlock(_previewBoard, *_next);
}

void Tetris::fetchNextBlock() {
    earseNextBlock();
    _curr = _next;
    _next = Block::RandomBlock();

    centerNextBlock();
    TopCenterCurrentBlock();
    paintCurrentBlock();
    paintNextBlock();
}

Tetris::Tetris(int row, int col) :
    _mainBoard(row, col), _previewBoard(6, 6),
    _mainBoardPos(2, 4), _previewBoardPos(_mainBoardPos.X + RealWidth(_mainBoard) + 3, _mainBoardPos.Y + 3) {

    Position pos;
    pos = TopCenterPosition(_mainBoard, _mainBoardPos, _mainBoardTitle.size());
    pos.Y -= 2;
    _mainBoardTitlePos = pos;

    pos = TopCenterPosition(_previewBoard, _previewBoardPos, _previewBoardTitle.size());
    pos.Y -= 2;
    _previewBoardTitlePos = pos;

    pos = BottomLeftPosition(_previewBoard, _previewBoardPos);
    pos.Y += 3;
    pos.X += _previewBoard.thickness() + 1;
    _speedPos = pos;

    pos.Y += 2;
    _scorePos = pos;

    pos.Y += 2;
    _comboPos = pos;

    _next = Block::RandomBlock();
    centerNextBlock();
}

void Tetris::run() {
    HideCursor();
    showMainTitle();
    showPreviewBoardTitle();

    paintMainBoard();
    showLevel();
    showScore();
    showCombo();

    fetchNextBlock();
    do {
        do {
            readOpeartion();
        } while (shiftDown());
        stackBlock();
        fetchNextBlock();
    } while (!gameOver());
    paintCurrentBlock();
}

