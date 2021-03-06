#pragma once
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Gracz
{
private:
	string nazwaGracza;
	int iloscPunktow = 0;
	string czasGry = "";
public:
	Gracz();
	Gracz(string nazwa);
	~Gracz();
	
	string UstawNazweGracza();

	void setNazwaGracza() { nazwaGracza = UstawNazweGracza(); }
	void setIloscPunktow(int ilosc) { iloscPunktow += ilosc; }
	void setCzasGry(string czas) { czasGry = czas; }

	string getNazwaGracza() { return nazwaGracza; }
	int getIloscPunktow() { return iloscPunktow; }
	string getCzasGry() { return czasGry; }

	void Zerowanie() { iloscPunktow = 0; }
};

