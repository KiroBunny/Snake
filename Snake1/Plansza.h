#pragma once
#include "Snake.h"
#include "xyio.h"
#include "Gracz.h"
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;
enum Predkosc
{
	latwy = 1000,	//1.0
	sredni = 500,	//2.0
	trudy = 250		//4.0
};
class Plansza
{
	int _szerokosc = 20;
	int _wysokosc = 20;
	char pole[55][55];	// p - puste,W - glowa weza, w - waz na danym polu, j - jablko na polu
	Snake _snake;
	Gracz* _gracz;
	int jablkoX = 0;
	int jablkoY = 0;
	
	Predkosc predkosc;
	int hr = 0, minu = 0, sec = 0;

	char klawisz = 'd';
	char poprzedniKlawisz = ' '; // Po starcie gry, w¹¿ bêdzie najpierw szedl w prawo
	
public:

	Plansza(int szerokosc, int wysokosc, Gracz* gr);

	void setSzerokosc(int szerokosc) { _szerokosc = szerokosc; }
	void setWysokosc(int wysokosc) { _wysokosc = wysokosc; }
	void setPredkosc(Predkosc pre) { predkosc = pre; }

	
	int getSzerokosc() { return _szerokosc; }
	int getWysokosc() { return _wysokosc; }
	
	//setcursor
	bool rysujPlansze();
	bool wyswietlSakeJablko();
	void wypelnijPustePole();
	void randomPolozenieSnake();
	void randdomPolozenieJablko();
	bool Sterowanie();
	void zmianaTabXXweza();
	void zmianaTabYYweza();
	int timer(int &min,int &sec);
};

