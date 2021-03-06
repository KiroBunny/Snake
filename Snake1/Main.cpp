#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Ustawienia.h"
#include "Gracz.h"
#include "xyio.h"
#include <vector>
using namespace std;

static int xorg_, yorg_;
static int xend_, yend_;
static int maxx_, maxy_;
static int x0_, y0_, y1_;
static int dx_, dy_, y2_;

enum Menu_Gry
{
	Poczatek,
	NowaGra,
	PoziomTrudnosci,
	Pomoc,
	Statystyki,
	KoniecGry
};
static Menu_Gry WykonajDialog();
static void TabelkaStatystyki(int& N, int& M);
static void TabelkaStatystykiDane(int I);
static void ZapiszWyniki(Gracz gr);
static string PomocInfo();
void setcursor(int x, int y);
int xyprintf(int x, int y, const char* format, ...);

string top10[10];
string tabNazwy[10];
int tabPunkty[10];
string tabCzas[10];

int main() {
	int N = 0, M = 0, I = 0;
	char znak;

	Menu_Gry polecenie = Poczatek;
	bool koniec = false;

	Gracz gracz;
	gracz.setNazwaGracza();

	Ustawienia* menu1 = new Ustawienia(&gracz);

	do {
		system("cls");
		menu1->WyswetlanieWstepu();
		polecenie = WykonajDialog();
		switch (polecenie)
		{
		case NowaGra:
			menu1->nowaGra();
			ZapiszWyniki(gracz);
			break;
		case PoziomTrudnosci:
			int n;
			printf(" [ WYBIERZ POZIOM TRUDNOSCI ]\n %d - prosty\n %d - sredni\n %d - trudny\n\n", poziom_trudnosci::prosty, poziom_trudnosci::sredni, poziom_trudnosci::trudny);
			scanf_s("%d", &n);
			menu1->setPoziomTrudnosci((poziom_trudnosci)n);
			break;
		case Pomoc:
			system("cls");
			cout << PomocInfo();
			printf("\n\n Wpisz dowolna cyfre lub litere, aby wrocic do menu\n");
			cin >> znak;
			break;
		case Statystyki:
			system("cls");
			cout << "\t\t\t\t\t	 [ STATYSTYKA ]\n\n";
			TabelkaStatystyki(N, M);
			TabelkaStatystykiDane(I);
			printf("\n\n Wpisz dowolna cyfre lub litere, aby wrocic do menu\n");
			cin >> znak;
			break;
		case KoniecGry:
			koniec = true;
			break;
		default:
			cout << " Wybierz poprawna opcje";
			break;
		}

	} while (!koniec);

	cout << "KONIEC GRY";
}

Menu_Gry WykonajDialog()
{
	Menu_Gry opcja;
	int x, n;
	printf("\n\t\t\t\t\t\t\t[ MENU ]\n\n\t\t\t\t\t\t %d - Nowa Gra\n\t\t\t\t\t\t %d - Poziom Trudnosci\n\t\t\t\t\t\t %d - Pomoc\n\t\t\t\t\t\t %d - Statystyki\n\t\t\t\t\t\t %d - Koniec Gry\n\n\n",
		NowaGra, PoziomTrudnosci, Pomoc, Statystyki, KoniecGry);
	scanf_s("%d", &n);
	opcja = (Menu_Gry)n;

	return opcja;
}


void TabelkaStatystyki(int& N, int& M)
{
	int x, y;
	x = x0_;
	y = y0_;
	y++; y++;
	xyprintf(x, y, "\t\t+---------------+-----------------------------+-----------------+----------------+");
	y++;
	xyprintf(x, y, "\t\t|      Lp.      |         Nazwa Gracza        |      Wynik      |      Czas      |");
	y++;
	xyprintf(x, y, "\t\t+---------------+-----------------------------+-----------------+----------------+");
	y++;
	N = (maxy_ - y - y0_ + 2 * yorg_) / 2;
	if (N <= 0) N = 5;
	M = 6;
	y1_ = y;
	y2_ = y1_ + N * 2;
	setcursor(0, 0);
}
void TabelkaStatystykiDane(int I)
{
	int x, y;
	x = x0_;
	y = y1_ + I * 2;
	if (y < y1_) y = y1_;
	else if (y >= y2_) y = y2_ - 2;
	int licznik = 1;

	ifstream plik("Statystyka1.txt", fstream::in);
	string wyraz;

	int indeks = 0;
	int indeksCzas = 0;
	int DlugoscWyniku = 0;

	if (plik.is_open())
	{
		while (getline(plik, wyraz))
		{
			for (size_t i = 0; i < wyraz.length() - 1; i++)
			{
				if (wyraz[i] == ';')
				{
					indeks = i;
				}
				if (wyraz[i] == '*')
				{
					indeksCzas = i;
				}
			}

			DlugoscWyniku = indeksCzas - indeks;

			string nazwaUzytkownika = wyraz.substr(0, indeks).c_str();
			string wynik = wyraz.substr(indeks + 1, DlugoscWyniku - 1).c_str();
			string czasUzytkownika = wyraz.substr(indeksCzas + 1).c_str();

			int dlugoscNazwy = nazwaUzytkownika.length();
			int temp = (29 - dlugoscNazwy) / 2;
			string str = "";

			int dlugoscWynik = wynik.length();
			int tempWynik = (17 - dlugoscWynik) / 2;
			string strWynik = "";

			int dlugoscCzas = czasUzytkownika.length();
			int tempCzas = (17 - dlugoscCzas) / 2;
			string strCzas = "";

			// Dla nazwa uzytkownika 
			for (size_t i = 0; i < temp; i++)
			{
				str += " ";
			}
			str += nazwaUzytkownika;
			if (dlugoscNazwy % 2 == 0)
			{
				temp += 1;
			}
			for (size_t i = 0; i < temp; i++)
			{
				str += " ";
			}

			// Dla wyniku 
			for (size_t i = 0; i < tempWynik; i++)
			{
				strWynik += " ";
			}
			strWynik += wynik;
			if (dlugoscWynik % 2 == 0)
			{
				tempWynik += 1;
			}

			for (size_t i = 0; i < tempWynik; i++)
			{
				strWynik += " ";
			}

			// Dla czasu 
			for (size_t i = 0; i < tempCzas; i++)
			{
				strCzas += " ";
			}
			strCzas += czasUzytkownika;
			for (size_t i = 0; i < (tempCzas); i++)
			{
				strCzas += " ";
			}

			if (licznik < 10)
			{
				xyprintf(x, y, "\t\t|       %d.      |%s|%s|%s|", licznik, str.c_str(), strWynik.c_str(), strCzas.c_str());
			}
			else
			{
				xyprintf(x, y, "\t\t|       %d.     |%s|%s|%s|", licznik, str.c_str(), strWynik.c_str(), strCzas.c_str());
			}
			y++;
			xyprintf(x, y, "\t\t+---------------+-----------------------------+-----------------+----------------+");
			y++;
			licznik++;
		}
	}

	plik.close();
}

void ZapiszWyniki(Gracz gr)
{
	// Pobieranie aktualnych wyników zapisanych z pliku
	ifstream plik("Statystyka1.txt", fstream::in);
	string wyraz;

	int iWyrazu = 0;
	int indeksPkt = 0;
	int indeksCzasu = 0;

	if (plik.is_open())
	{
		while (getline(plik, wyraz))
		{
			for (size_t i = 0; i < wyraz.length(); i++)
			{
				if (wyraz[i] == ';')
					indeksPkt = i;
				if (wyraz[i] == '*')
					indeksCzasu = i;
			}

			tabNazwy[iWyrazu] = wyraz.substr(0, indeksPkt).c_str();
			tabPunkty[iWyrazu] = atoi(wyraz.substr(indeksPkt + 1, indeksCzasu - indeksPkt - 1).c_str());
			tabCzas[iWyrazu] = wyraz.substr(indeksCzasu + 1);
			iWyrazu++;
		}
	}
	plik.close();

	// Zapisywanie aktualnych danych do tablicy, w celu porównania i posortowania wyników.
	int identyfikator = 9;
	for (int i = 9; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (tabPunkty[j] < tabPunkty[j + 1])
			{
				string a;
				a = tabNazwy[j + 1];
				tabNazwy[j + 1] = tabNazwy[j];
				tabNazwy[j] = a;

				int b;
				b = tabPunkty[j + 1];
				tabPunkty[j + 1] = tabPunkty[j];
				tabPunkty[j] = b;

				string c;
				c = tabCzas[j + 1];
				tabCzas[j + 1] = tabCzas[j];
				tabCzas[j] = c;

			}

			if (gr.getIloscPunktow() > tabPunkty[j])
				identyfikator = j;
		}
	}
	
	// Zapisanie 10 poprawnych wyników
	int k = 0;
	for (int i = 0; i < 10; i++)
	{
		if (i == identyfikator)
		{
			string linia;
			linia += gr.getNazwaGracza();
			linia += ';';
			linia += to_string(gr.getIloscPunktow());
			linia += '*';
			linia += gr.getCzasGry();
			top10[i] = linia;
			k--;
		}
		else
		{
			string linia;
			linia += tabNazwy[k];
			linia += ';';
			linia += to_string(tabPunkty[k]);
			linia += '*';
			linia += tabCzas[k];
			top10[i] = linia;
		}
		k++;
	}

	// Zapis 10 wartoœci do pliku
	fstream plik1("Statystyka1.txt", ios::trunc | ios::out);
	if (plik1.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			plik1 << top10[i] << endl;
		}
	}
	plik1.close();
}

string PomocInfo()
{
	string info = "";
	info += " [ POMOC ]\n\n W grze gracz kontroluje dlugie i cienkie stworzenie, podobne do weza, ";
	info += "\n ktore porusza sie po obramowanej planszy zbierajac jedzenie, ";
	info += "\n probujac nie uderzyc wlasna glowa o sciany otaczajace plansze gry, a takze o czesc wlasnego ciala.";
	info += "\n Kiedy waz zje jablko, jego ogon robi sie coraz dluzszy, co utrudnia gre.";
	info += "\n Gracz kontroluje kierunek ruchu weza za pomoca klawiszy WSAD (w - gora, s - dol, a - lewo, d - prawo.";
	info += "\n Gracz nie moze zatrzymac weza, gdy gra jest w toku.";
	return info;
}