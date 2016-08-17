#pragma once

#include "../core/Position.h"

#ifdef WIN32
#include <conio.h>
#include <windows.h>

#define print printf
#define getch _getch

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#else
#define UNIX
#include <ncurses.h>
#define print printw
#endif

void ClearScreen();

void CursorGoto(Position pos);

void CursorRight(int dx = 1);

void CursorHide();

void CursorShow();