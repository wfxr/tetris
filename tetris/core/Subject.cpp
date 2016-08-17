#include <memory>

using std::shared_ptr;

#include "subject.h"
#include "observer.h"


void Subject::subscribe(shared_ptr<Observer> observer) {
    _observers.push_back(observer);
}

void Subject::unsubscribe(std::shared_ptr<Observer> observer) {
    auto fid = find(_observers.begin(), _observers.end(), observer);
    if (fid != _observers.end()) _observers.erase(fid);
}

void Subject::notifyEraseCurrentBlock() {
    for (auto obs : _observers)
        obs->eraseCurrentBlock();
}

void Subject::notifyPaintCurrentBlock() {
    for (auto obs : _observers)
        obs->paintCurrentBlock();

}

void Subject::notifyEraseNextBlock() {
    for (auto obs : _observers)
        obs->eraseNextBlock();
}

void Subject::notifyPaintNextBlock() {
    for (auto obs : _observers)
        obs->paintNextBlock();
}

void Subject::notifyPaintBoard() {
    for (auto obs : _observers)
        obs->updateBoard();
}

void Subject::notifyUpdateGameInfo() {
    for (auto obs : _observers)
        obs->updateGameInfo();
}