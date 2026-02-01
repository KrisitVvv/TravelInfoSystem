#include <stdio.h>
#include <Windows.h>

void color(short x){
    if (x >= 0 && x <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	
    else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void HideCursor(int num)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, num };  
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}