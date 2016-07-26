#pragma once

#include <vector>
#include <iostream>

#include "block.h"

using std::vector;
using std::cout;
using std::endl;

class Board {
public:
	Board(int row = 20, int col = 10) 
		: _row(row), _col(col) {
		_board.assign(row, vector<int>(col));
	}

	void set(int row, int col, int value = 1) { _board[row][col] = value; }
	int get(int row, int col) const { return _board[row][col]; }

	int height() const { return _row; }
	int width() const { return _col; }

	void paint() {
		system("cls");
		cout << "©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´" << endl;
		for (int r = 0; r < _row; ++r) {
			cout << "©¦";
			for (int c = 0; c < _col; ++c)
				if (_board[r][c])
					cout << "¨~";
				else
					cout << "  ";
			cout << "©¦" << endl;
		}
		cout << "©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼" << endl;
	}

private:
	int _row;
	int _col;
	vector<vector<int>> _board;
};
