#include "xyio.h"

void setcursor(int x, int y) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pkt = { x,y };
	SetConsoleCursorPosition(ekran, pkt);
}

int xyprintf(int x, int y, const char* format, ...)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list arg;
	va_start(arg, format);
	int wynik = vsprintf(tekst, format, arg);

	if (wynik >= 0)
	{
		znaki = (DWORD)wynik;
		setcursor(x, y);
		sukces = WriteConsole(ekran, tekst, znaki, NULL, NULL);
		if (!sukces)wynik = EOF;
	}
	va_end(arg);
	return wynik;
}