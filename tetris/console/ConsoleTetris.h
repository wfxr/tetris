#pragma once
#include <memory>
#include <string>
#include "../core/Observer.h"
#include "../core/Tetris.h"
#include "../core/Position.h"

class ConsoleTetris final: public Observer, 
                           public std::enable_shared_from_this<ConsoleTetris> {
public:
    static std::shared_ptr<ConsoleTetris> Create(int rows, int cols);

    void run();

private:
    void paintCurrentBlock() override;
    void eraseCurrentBlock() override;

    void paintNextBlock() override;
    void eraseNextBlock() override;

    void updateBoard() override;
    void updateGameInfo() override;

    static void PaintBlock(Position boardPos, shared_ptr<Block> block, const std::string& brush);
    static void AlignHorizontalCenter(const Border& border, Position& position, int width);
    static void PaintBoard(const Board& board, Position pos);
    static void PaintBorder(const Board& board, Position pos);

    static int RealWidth(const Board& board) { return 4 + board.width() * 2; }
    static int RealHeight(const Board& board) { return 2 + board.height(); }

    std::string ConsoleTetris::levelText() const;
    std::string ConsoleTetris::scoreText() const;
    std::string ConsoleTetris::comboText() const;

    void printTitle() const;
    void readOperation();

    ConsoleTetris(int rows, int cols, int previewBoardSize = 6);

    const static std::string _blockBrush;
    const static std::string _borderBrush;
    const static std::string _eraseBrush;

    Tetris _game;
    Position _mainBoardPos;
    Position _previewBoardPos;
    Position _statusPos;
    bool _quit = false;
};
