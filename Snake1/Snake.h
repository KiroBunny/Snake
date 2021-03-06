#pragma once
#include <cstdlib> 
class Snake
{
private:
	int wspolrzednaXGlowy = 0;
	int wspolrzednaYGlowy = 0;
	int dlugosc = 4;
	int tabWspX[1000];
	int tabWspY[1000];

public:
	void poczatkowaWartoscTablic()
	{
		for (size_t i = 0; i < dlugosc; i++)
		{
			tabWspX[i] = -1;
			tabWspY[i] = -1;
		}
	}
	void setWspolrzednaXGlowy(int wspX) { wspolrzednaXGlowy = wspX; }
	void setWspolrzednaYGlowy(int wspY) { wspolrzednaYGlowy = wspY; }
	void dodajDlugosc(int oIle) { dlugosc += oIle; }
	void setTabWspX(int index, int wspX);
	void setTabWspY(int index, int wspY);
	void resetDlugosc() { dlugosc = 4; }

	int getWspolrzednaXGlowy() { return wspolrzednaXGlowy; }
	int getWspolrzednaYGlowy() { return wspolrzednaYGlowy; }
	int getDlugosc() { return dlugosc; }
	int getTabWspX(int index);
	int getTabWspY(int index);
};

