#include "Gracz.h"
Gracz::Gracz() {}
Gracz::Gracz(string nazwa)
	: nazwaGracza(nazwa) {}
Gracz::~Gracz() {}

string Gracz::UstawNazweGracza() 
{
	string nazwa;
	cout << "Podaj nazwe nowego Gracza: " << endl;
	cin >> nazwa;
	return nazwa;
}