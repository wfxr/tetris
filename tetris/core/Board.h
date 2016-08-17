#pragma once

#include "Border.h"
#include <vector>

class Board : public Border {
public:
    explicit Board(int height = 20, int width = 10) 
        : Border(width, height), _board(height, vector<int>(width)) { }

    void set(int h, int v, int value = 1) { _board[v][h] = value; }
    int at(int h, int v) const { return _board[v][h]; }

    void reset() {
        for (auto& row : _board)
            for (auto &cell : row)
                cell = 0;
    }

    int eliminateRows() {
        vector<vector<int>> new_board;
        auto eliminated = 0;
        for (auto& row : _board) {
            auto shouldErase = true;
            for (auto& cell: row) {
                if (cell == 0) {
                    shouldErase = false;
                    break;
                }
            }
            if (shouldErase)
                ++eliminated;
            else
                new_board.push_back(row);
        }

        new_board.insert(new_board.begin(), eliminated, vector<int>(width()));
        _board = new_board;
        return eliminated;
    }

private:
    vector<vector<int>> _board;
};
