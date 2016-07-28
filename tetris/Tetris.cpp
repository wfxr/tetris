#include "Tetris.h"
#include "ConsoleUtility.h"

milliseconds Tetris::operationTime() { return milliseconds(1000 / speed); }

bool Tetris::isOverlap() const { return isOverlap(_curr); }

bool Tetris::isOverlap(shared_ptr<Block> block) const {
	for (int h = block->left(); h < block->right(); ++h)
		for (int v = block->top(); v < block->bottom(); ++v)
			if (block->at(h, v) && _mainBoard.at(h, v))
				return true;
	return false;
}

bool Tetris::reachLeftBorder() const { return _curr->left() == 0; }

bool Tetris::reachRightBorder() const { return _curr->right() == _mainBoard.width(); }

bool Tetris::reachBottomBorder() const { return _curr->bottom() == _mainBoard.height(); }

void Tetris::stackBlock() {
	for (int h = _curr->left(); h < _curr->right(); ++h)
		for (int v = _curr->top(); v < _curr->bottom(); ++v)
			if (_curr->at(h, v)) _mainBoard.set(h, v);
}

bool Tetris::rotate() {
	if (!canRotate()) return false;

	eraseCurrentBlock();
	_curr->rotate();
	paintCurrentBlock();
	return true;
}

bool Tetris::canRotate() {
	auto block = make_shared<Block>(*_curr);
	block->rotate();

	auto br = block->right();
	auto bb = block->bottom();
	if (block->right() > _mainBoard.width() || block->bottom() > _mainBoard.height())
		return false;
	return !isOverlap(block);
}

bool Tetris::canShiftLeft() {
	if (reachLeftBorder())
		return false;
	for (int h = _curr->left(); h < _curr->right(); ++h)
		for (int v = _curr->top(); v < _curr->bottom(); ++v)
			if (_curr->at(h, v) && _mainBoard.at(h - 1, v))
				return false;
	return true;
}

bool Tetris::canShiftRight() {
	if (reachRightBorder())
		return false;
	for (int h = _curr->left(); h < _curr->right(); ++h)
		for (int v = _curr->top(); v < _curr->bottom(); ++v)
			if (_curr->at(h, v) && _mainBoard.at(h + 1, v))
				return false;
	return true;
}

bool Tetris::canShiftDown() {
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

void Tetris::paintBoard(const Board & board, Position pos, const string & brush) {
	CursorGoto(pos);
	cout << "©°";
	for (int x = 0; x < board.width(); ++x)
		cout << "©¤©¤";
	cout << "©´";
	++pos.Y;

	for (int y = 0; y < board.height(); ++y, ++pos.Y) {
		CursorGoto(pos);
		cout << "©¦";
		for (int x = 0; x < board.width(); ++x)
			if (board.at(x, y))
				cout << "¨~";
			else
				cout << "  ";
		cout << "©¦";
	}

	CursorGoto(pos);
	cout << "©¸";
	for (int x = 0; x < board.width(); ++x)
		cout << "©¤©¤";
	cout << "©¼";
}

void Tetris::paintBlock(const Board& board, Position boardPos, shared_ptr<Block> block, const string& brush /*= "¨~"*/) {
	auto blockPos = boardPos;
	blockPos.X += board.thickness() + block->left() * 2;
	blockPos.Y += board.thickness() + block->top();

	for (int v = block->top(); v < block->bottom(); ++v, ++blockPos.Y) {
		CursorGoto(blockPos);
		for (int h = block->left(); h < block->right(); ++h) {
			if (block->at(h, v))
				cout << brush;
			else
				CursorRight(2);
		}
	}
}

int Tetris::realWidth(const Board & board) { return board.thickness() * 2 + board.width() * 2; }

void Tetris::eraseCurrentBlock() {
	paintCurrentBlock("  ");
}

void Tetris::paintCurrentBlock(const string& brush)
{
	paintBlock(_mainBoard, _mainBoardPos, _curr, brush);
}

void Tetris::paintNextBlock(const string & brush) {
	paintBlock(_previewBoard, _previewBoardPos, _next, brush);
}

void Tetris::earseNextBlock() { paintNextBlock("  "); }

void Tetris::paintMainBoard() { paintBoard(_mainBoard, _mainBoardPos); }

void Tetris::paintPreviewBoard() { paintBoard(_previewBoard, _previewBoardPos); }

shared_ptr<Block> Tetris::randomBlock() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> typeRand(0, BlockShapesCount - 1);
	uniform_int_distribution<> formRand;

	auto type = static_cast<ShapeCategory>(typeRand(gen));
	auto form = formRand(gen);
	return Block::CreateBlock(type, 0, 0, form);
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

bool Tetris::gameOver() { return isOverlap(_curr); }

int Tetris::eliminateBlocks() {
	auto rows = _mainBoard.eliminateRows();
	if (rows)
		paintMainBoard();
	return rows * rows;
}

void Tetris::HorizontalCenterBlock(const Board & board, Position boardPos, Block & block) {
	block.setPosition((board.width() - block.width()) / 2, block.top());
}

void Tetris::VerticalCenterBlock(const Board & board, Position boardPos, Block & block) {
	block.setPosition(block.left(), (board.height() - block.height()) / 2);
}

void Tetris::TopCenterCurrentBlock() {
	_curr->setPosition(0, 0);
	HorizontalCenterBlock(_mainBoard, _mainBoardPos, *_curr);
}

void Tetris::centerNextBlock() {
	HorizontalCenterBlock(_previewBoard, _previewBoardPos, *_next);
	VerticalCenterBlock(_previewBoard, _previewBoardPos, *_next);
}

void Tetris::fetchNextBlock() {
	earseNextBlock();
	_curr = _next;
	_next = randomBlock();

	centerNextBlock();
	TopCenterCurrentBlock();
}

Tetris::Tetris(int row, int col) :
	_mainBoard(row, col), _previewBoard(6, 6),
	_curr(), _next(randomBlock()),
	_mainBoardPos(), _previewBoardPos(realWidth(_mainBoard) + 1, 2) {
	HideCursor();
	centerNextBlock();
}
