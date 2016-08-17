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

    // ��ȡ��һ����
    void fetchNextBlock();

    // ������ѻ���board
    void stackBlock();

    // ÿ����һ����ִ�в�����ʱ��
    std::chrono::milliseconds operationTime() const;

    // ��ⷽ���Ƿ���Խ�����ת/����/����/����
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

    // ���뷽��
    static void AlignHorizontalCenter(const Border& border, Block& block);
    static void AlignVerticalCenter(const Border& border, Block& block);
    static void AlignCenter(const Border& border, Block& block);
    static void AlignTopCenter(const Border& border, Block& block);

    // ����÷�
    int compute_score(int rows) const;

    // ��ⷽ���Ƿ񵽴���/��/�±߽�
    bool reachLeft() const;
    bool reachRight() const;
    bool reachBottom() const;

    // ��ⷽ����board�еķ����Ƿ��ص�
    static bool IsOverlap(const Board& board, shared_ptr<Block> block);

    // ������
    void eliminateRows();

    // �����ȼ�
    void levelUp();
};
