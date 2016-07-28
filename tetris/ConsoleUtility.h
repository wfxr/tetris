#pragma once

#include <windows.h>
#include "Position.h"

void CursorGoto(COORD pos) {
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void CursorGoto(Position pos) {
	CursorGoto(COORD{ (short)pos.X, (short)pos.Y });
}

COORD CursorPos() {
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  info;
	GetConsoleScreenBufferInfo(output, &info);
	return info.dwCursorPosition;
}

void CursorRight(int dx = 1) {
	auto pos = CursorPos();
	pos.X += dx;
	CursorGoto(pos);
}

void HideCursor() {
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(output, &cursor);
}
