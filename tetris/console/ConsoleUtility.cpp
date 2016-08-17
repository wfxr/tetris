#include "ConsoleUtility.h"

#include <windows.h>

void ClearScreen() {
#ifdef WIN32
    system("cls");
#else
    clear();
#endif
}

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

void CursorRight(int dx) {
    auto pos = CursorPos();
    pos.X += dx;
    CursorGoto(pos);
}

void CursorHide() {
    static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(output, &cursor);
}

void CursorShow() {
    static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = TRUE;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(output, &cursor);
}
