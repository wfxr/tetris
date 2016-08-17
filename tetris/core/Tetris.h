#pragma once

#include <chrono>
#include <memory>

#include "Subject.h"
#include "Block.h"
#include "Board.h"

class Tetris : public Subject {
public:
    explicit Tetris(int row = 20, int col = 10, int previewBoardSize = 6);

    bool rotate();
    bool shiftDown();
    bool shiftLeft();
    bool shiftRight();
    bool gameOver() const;
    void reset();

    std::shared_ptr<Block> currentBlock() const { return _curr; }

    std::shared_ptr<Block> nextBlock() const { return _next; }

    const Board& getMainBoard() const { return _board; }
    const Board& getPreviewBoard() const { return _previewBoard; }

    // 获取下一方块
    void fetchNextBlock();

    // 将方块堆积到board
    void stackBlock();

    // 每下落一步可执行操作的时间
    std::chrono::milliseconds operationTime() const;

    // 检测方块是否可以进行旋转/左移/右移/下移
    bool canRotate() const;
    bool canShiftLeft() const;
    bool canShiftRight() const;
    bool canShiftDown() const;

    int level() const { return _level; }
    int score() const { return _score; }
    int combo() const { return _combo; }
private:
    const int MaxLevel = 10;
    std::shared_ptr<Block> _curr;
    std::shared_ptr<Block> _next;
    Board _board;
    Board _previewBoard;

    int _level = 1;
    int _score = 0;
    int _combo = 0;

    // 对齐方块
    static void AlignHorizontalCenter(const Border& border, Block& block);
    static void AlignVerticalCenter(const Border& border, Block& block);
    static void AlignCenter(const Border& border, Block& block);
    static void AlignTopCenter(const Border& border, Block& block);

    // 计算得分
    int compute_score(int rows) const;

    // 检测方块是否到达左/右/下边界
    bool reachLeft() const;
    bool reachRight() const;
    bool reachBottom() const;

    // 检测方块与board中的方块是否重叠
    static bool IsOverlap(const Board& board, shared_ptr<Block> block);

    // 消除行
    void eliminateRows();

    // 提升等级
    void levelUp();
};
