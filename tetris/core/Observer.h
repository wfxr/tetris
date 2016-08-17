#pragma once

class Observer {
public:
    virtual ~Observer() {}

    virtual void paintCurrentBlock() = 0;
    virtual void eraseCurrentBlock() = 0;
    virtual void paintNextBlock() = 0;
    virtual void eraseNextBlock() = 0;
    virtual void updateBoard() = 0;
    virtual void updateGameInfo() = 0;
};