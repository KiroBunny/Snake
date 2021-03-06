#pragma once
#include <string>
#include <iostream>
#include <sstream>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Plansza.h"
#include "Gracz.h"

using namespace std;
enum class poziom_trudnosci
{
	prosty,		// predkosc 1.0		wielkosc 70x50
	sredni,		//pred 2.0			
	trudny		//pred 4.0			
};

class Ustawienia
{
private:
	poziom_trudnosci poziomTrudnosci = poziom_trudnosci::sredni;
	Plansza* _plansza;                        
	Gracz* _gracz;

public:
	Ustawienia(Gracz* gr);
	Ustawienia(const poziom_trudnosci poziom, Gracz* gr);
	~Ustawienia();

	void setPoziomTrudnosci(const poziom_trudnosci poziom) { poziomTrudnosci = poziom; };

	poziom_trudnosci getPoziomTrudnosci() const { return poziomTrudnosci; };

	void nowaGra();
	
	//protected:
	void WyswetlanieWstepu()
	{
		printf("\t\t\t\t#####################################################\n");
		printf("\t\t\t\t#\t                     _\t\t\t    #\n");
		printf("\t\t\t\t#\t     ___ _ __   __ _| | _____  \t\t    #\n");
		printf("\t\t\t\t#\t    / __| '_ \\ / _` | |/ / _ \\ \t\t    #\n");
		printf("\t\t\t\t#\t    \\__ \\ | | | (_| |   <  __/ \t\t    #\n");
		printf("\t\t\t\t#\t    |___/_| |_|\\__,_|_|\\_\\___| \t\t    #\n");
		printf("\t\t\t\t#\t                      \t\t\t    #\n");
		printf("\t\t\t\t# Edyta Palka  |  Katarzyna Norys  |  Lukasz Langer #\n");
		printf("\t\t\t\t#####################################################\n");
	}
	
};

