#pragma once

class Border {
public:
    Border(int width, int height) : _width(width), _height(height)  {}

    virtual ~Border() {}

    int width() const {
        return _width;
    }

    int height() const {
        return _height;
    }

private:
    int _width;
    int _height;
};

