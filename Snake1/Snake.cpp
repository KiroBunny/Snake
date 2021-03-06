#include "Snake.h"

void Snake::setTabWspX(int index, int wspX)
{
	if (index == 0)
		tabWspX[0] = wspolrzednaXGlowy;
	if (index < dlugosc)
		tabWspX[index] = wspX;
}

void Snake::setTabWspY(int index, int wspY)
{
	if (index == 0)
		tabWspY[0] = wspolrzednaYGlowy;
	if (index < dlugosc)
		tabWspY[index] = wspY;
}

int Snake::getTabWspX(int index)
{
	if(index < dlugosc && index >= 0)
	return tabWspX[index];
}

int Snake::getTabWspY(int index)
{
	if (index < dlugosc && index >=0)
		return tabWspY[index];
}
