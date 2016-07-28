#pragma once

#include <windows.h>

void CursorGoto(int x, int y) {
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, { (short)x, (short)y });
}

COORD CursorPos() {
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  info;
	GetConsoleScreenBufferInfo(output, &info);
	return info.dwCursorPosition;
}

void CursorRight(int dx) {
	auto pos = CursorPos();
	CursorGoto(pos.X + dx, pos.Y);
}

void HideCursor() {
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(output, &cursor);
}
