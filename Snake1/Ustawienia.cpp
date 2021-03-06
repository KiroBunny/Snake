#include "Ustawienia.h"

#define _CRT_SECURE_NO_WARNINGS 
Ustawienia::Ustawienia(Gracz* gr) {
	_plansza = new Plansza(20, 15, gr);
	_gracz = gr;
}
Ustawienia::Ustawienia(const poziom_trudnosci poziom, Gracz* gr)
	:poziomTrudnosci(poziom){
	_plansza = new Plansza(20, 15, gr);
	_gracz = gr;
}
Ustawienia::~Ustawienia() {}

void Ustawienia::nowaGra()
{
	system("cls");
	this->WyswetlanieWstepu();
	cout << endl << endl << endl;
	string e;

	if (poziomTrudnosci == poziom_trudnosci::prosty)
	{
		_plansza->setSzerokosc(55);
		_plansza->setWysokosc(25);
		_plansza->setPredkosc(Predkosc::latwy);
	}
	else if (poziomTrudnosci == poziom_trudnosci::sredni)
	{
		_plansza->setSzerokosc(40);
		_plansza->setWysokosc(20);
		_plansza->setPredkosc(Predkosc::sredni);
	}
	else if (poziomTrudnosci == poziom_trudnosci::trudny)
	{
		_plansza->setSzerokosc(20);
		_plansza->setWysokosc(15);
		_plansza->setPredkosc(Predkosc::trudy);
	}

	//Inicjowanie poczatkowych wartosci planszy
	_plansza->wypelnijPustePole();
	_plansza->randomPolozenieSnake();
	_plansza->randdomPolozenieJablko();
	_plansza->rysujPlansze();

	do {} while (!_plansza->wyswietlSakeJablko());
	
	printf("\n\n Wpisz dowolna cyfre lub litere, aby wrocic do menu\n");
	cin >> e;
	e.clear();
}
