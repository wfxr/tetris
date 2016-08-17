#pragma once

#include <list>
#include <memory>

class Observer;

class Subject {
public:
    virtual ~Subject() {}

    void subscribe(std::shared_ptr<Observer> observer);
    void unsubscribe(std::shared_ptr<Observer> observer);
    void notifyEraseCurrentBlock();
    void notifyPaintCurrentBlock();
    void notifyEraseNextBlock();
    void notifyPaintNextBlock();
    void notifyPaintBoard();
    void notifyUpdateGameInfo();
private:
    std::list<std::shared_ptr<Observer>> _observers;
};
