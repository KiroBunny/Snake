#include "Plansza.h"
#include <time.h>
#include <windows.h>

void setcursor(int x, int y);

int Plansza::timer(int& minu, int& sec)
{ //Obliczanie czasu gry
	int hr = 0;
	while (true)
	{
		sec += predkosc;
		if (sec==60000)
		{
			minu++;
			sec = 0;
			if (minu == 60)
			{
				hr++;
				minu = 0;
				if (hr == 60)
				{
					hr = 0;
				}
			}
		}
		return hr;
	}
}

Plansza::Plansza(int szerokosc, int wysokosc, Gracz* gr)
{
	_wysokosc = wysokosc;
	_szerokosc = szerokosc;
	_gracz = gr;
	_snake.poczatkowaWartoscTablic();
	hr = 0, minu = 0, sec = 0;
}

bool Plansza::rysujPlansze()
{
	system("cls");
	cout << endl; cout << endl;

	for (int i = 0; i < _szerokosc; i++)
	{
		cout << "__";
	}
	cout << "" << endl;

	for (int i = 0; i < _wysokosc-1; i++)
	{
		cout << "|";
		for (int j = 0; j < _szerokosc; j++)
		{
			cout << "  ";
		}
		cout << "|" << endl;
	}

	cout << "|";
	for (int i = 0; i < _szerokosc; i++)
	{
		cout << "--";
	}
	cout << "|" << endl;

	bool kGry = Sterowanie();
	
	return kGry;
}

bool Plansza::wyswietlSakeJablko()
{
	int hr = timer(minu, sec);
	string czas;
	setcursor(0, 0);
	cout << " Zdobyte punkty: " << _gracz->getIloscPunktow() << endl;
	cout << to_string(minu) << " : " << to_string(sec / 1000) << "   " << endl;
	czas = to_string(minu) + ":" + to_string(sec / 1000);
	_gracz->setCzasGry(czas);

	cout << " ";
	for (size_t i = 0; i < _wysokosc - 1; i++) {
		for (size_t j = 0; j < _szerokosc; j++)
		{
			if (pole[i][j] == 'W') {
				setcursor((j * 2) + 1, i + 3);
				cout << "\xB2\xB2";
			}
			else if (pole[i][j] == 'w') {
				setcursor((j * 2) + 1, i + 3);
				cout << "\xB0\xB1";
			}
			else if (pole[i][j] == 'p') {
				setcursor((j * 2) + 1, i + 3);
				cout << "  ";
			}
			else if (pole[i][j] == 'j') {
				setcursor((j * 2) + 1, i + 3);
				cout << "\xE0 ";
			}
		}
	}
	setcursor(0, _wysokosc + 1);
	return Sterowanie();
}

void Plansza::wypelnijPustePole()
{
	for (size_t i = 0; i < 25; i++)
	{
		for (size_t j = 0; j < 55; j++)
		{
			pole[i][j] = 'p';
		}
	}
	 hr = 0, minu = 0, sec = 0;
	 _gracz->Zerowanie();
	 _snake.resetDlugosc();
	 _snake.poczatkowaWartoscTablic();
}

void Plansza::randomPolozenieSnake()
{
	srand(time(NULL));
	int X = rand() % (_szerokosc-2);
	int Y = rand() % (_wysokosc-2);

	_snake.setWspolrzednaXGlowy(X);
	_snake.setWspolrzednaYGlowy(Y);
	_snake.setTabWspX(0, X);
	_snake.setTabWspY(0, Y);
	pole[Y][X] = 'W';
}

void Plansza::randdomPolozenieJablko()
{
	do {
		jablkoX = rand() % (_szerokosc-2);
		jablkoY = rand() % (_wysokosc -2);
	} while (pole[jablkoY][jablkoX] != 'p');
	pole[jablkoY][jablkoX] = 'j';
}

bool Plansza::Sterowanie()
{
	bool koniecGry = false;
	int x, y;
		Sleep(predkosc); // Pół sekundy na start
		if (_kbhit())
			klawisz = _getch();
		
		// Poprawne sprawdzanie warunków, idąc w prawo, wąż nie może skręcić w lewo
		if (poprzedniKlawisz == 'd') {
			if (klawisz == 'a')
			{
				klawisz = 'd';
				return false;
			}
		}
		else if (poprzedniKlawisz == 's') {
			if (klawisz == 'w') {
				klawisz = 's';
				return false;
			}
		}
		else if (poprzedniKlawisz == 'a') {
			if (klawisz == 'd') {
				klawisz = 'a';
				return false;
			}
		}
		else if (poprzedniKlawisz == 'w') {
			if (klawisz == 's') {
				klawisz = 'w';
				return false;
			}
		}

		//Sprawdzenie czy waz zjada samego siebie
		for (size_t i = 1; i < _snake.getDlugosc(); i++)
		{
			if (_snake.getWspolrzednaXGlowy() == _snake.getTabWspX(i) && _snake.getWspolrzednaYGlowy() == _snake.getTabWspY(i))
				return true;
		}

		// Zmniejszenie pola wyświetlania węża - koniec ogonu
		pole[_snake.getTabWspY(_snake.getDlugosc() - 1)][_snake.getTabWspX(_snake.getDlugosc() - 1)] = 'p';
		//cout << _snake.getTabWspY(_snake.getDlugosc() - 1) << " ;;;; " << _snake.getDlugosc() - 1;

		//sterowanie
		if (klawisz == 'w' || klawisz == 'W') {
			poprzedniKlawisz = 'w';
			if ((_snake.getWspolrzednaYGlowy() - 1) < 0) koniecGry = true;
			_snake.setWspolrzednaYGlowy(_snake.getWspolrzednaYGlowy() - 1);
		}
		else if (klawisz == 'd' || klawisz == 'D') {
			poprzedniKlawisz = 'd';
			if ((_snake.getWspolrzednaXGlowy() + 1) == _szerokosc) koniecGry = true;
			_snake.setWspolrzednaXGlowy(_snake.getWspolrzednaXGlowy() + 1);
		}
		else if (klawisz == 's' || klawisz == 'S') {
			poprzedniKlawisz = 's';
			if ((_snake.getWspolrzednaYGlowy() + 1) == _wysokosc-1) koniecGry = true;
			_snake.setWspolrzednaYGlowy(_snake.getWspolrzednaYGlowy() + 1);
		}
		else if (klawisz == 'a' || klawisz == 'A') {
			poprzedniKlawisz = 'a';
			if ((_snake.getWspolrzednaXGlowy() - 1) < 0) koniecGry = true;
			_snake.setWspolrzednaXGlowy(_snake.getWspolrzednaXGlowy() - 1);
		}
		// Przerwanie gry
		else if (klawisz == 'p') {
			klawisz = ' ';
			koniecGry = true;
		}
		
		zmianaTabYYweza();
		zmianaTabXXweza();

		//Ustawienie glowy oraz ciala w tablicy pole
		pole[_snake.getTabWspY(0)][_snake.getTabWspX(0)] = 'W';
		pole[_snake.getTabWspY(1)][_snake.getTabWspX(1)] = 'w';

		// Zjadanie jablka
		if (pole[_snake.getWspolrzednaYGlowy()][_snake.getWspolrzednaXGlowy()] == pole[jablkoY][jablkoX])
		{
			_gracz->setIloscPunktow(50);
			randdomPolozenieJablko();
			_snake.dodajDlugosc(1);
		}
		return koniecGry;
}

void Plansza::zmianaTabXXweza()
{   // Z kazdym poruszeniem weza o 1 kratke zmieniane sa wspolrzedne jego ciala
	int wsp;
	int wsp0 = _snake.getTabWspX(0);
	_snake.setTabWspX(0, _snake.getWspolrzednaXGlowy());
	for (size_t i = 1; i < _snake.getDlugosc(); i++)
	{
		wsp = _snake.getTabWspX(i);
		_snake.setTabWspX(i, wsp0);
		wsp0 = wsp;
	}
}

void Plansza::zmianaTabYYweza()
{
	int wsp;
	int wsp0 = _snake.getTabWspY(0);
	_snake.setTabWspY(0, _snake.getWspolrzednaYGlowy());
	for (size_t i = 1; i < _snake.getDlugosc(); i++)
	{
		wsp = _snake.getTabWspY(i);
		_snake.setTabWspY(i, wsp0);
		wsp0 = wsp;
	}
}