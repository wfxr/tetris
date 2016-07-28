#pragma once

#include <vector>
#include <iostream>

#include "Block.h"

using std::vector;
using std::cout;
using std::endl;

class Board {
public:
	Board(int row = 20, int col = 10) 
		: _row(row), _col(col), _board(row, vector<int>(col)) { }

	void set(int h, int v, int value = 1) { _board[v][h] = value; }
	int at(int h, int v) const { return _board[v][h]; }

	int height() const { return _row; }
	int width() const { return _col; }

	int eliminateRows() {
		vector<vector<int>> new_board;
		int eliminated = 0;
		for (int r = 0; r < _row; ++r) {
			auto shouldRetain = false;
			for (int c = 0; c < _col; ++c) {
				if (_board[r][c] == 0) {
					shouldRetain = true;
					break;
				}
			}
			if (shouldRetain)
				new_board.push_back(_board[r]);
			else
				++eliminated;
		}
		new_board.insert(new_board.begin(), eliminated, vector<int>(_col));
		_board = new_board;
		return eliminated;
	}

	int thickness() const { return _thickness; }
private:
	int _row;
	int _col;
	int _thickness = 1;
	vector<vector<int>> _board;
};
