#include "Fruit.h"

Fruit::Fruit() : fruitCordX(0), fruitCordY(0), fruitColor(0) {}

int Fruit::getColor() { return fruitColor; }
int Fruit::getCordX() { return fruitCordX; }
int Fruit::getCordY() { return fruitCordY; }

void Fruit::setColor(int fruitColor) { this->fruitColor = fruitColor; }
void Fruit::setCordX(int fruitCordX) { this->fruitCordX = fruitCordX; }
void Fruit::setCordY(int fruitCordY) { this->fruitCordY = fruitCordY; }

void Fruit::addFruit(int colorField)
{
	fruitCordX = 40 + rand() % 40; 
	fruitCordY = 7 + rand() % 20;

	do
	{
		fruitColor = allColorFruit.at(rand() % allColorFruit.size());
	} while (fruitColor == colorField); // cicl povtoryaetsya esli tsvet fructa sovpadaet s tsvetom polya

	if (fruitCordX % 2 != 0)
		fruitCordX = fruitCordX - 1;
}

void Fruit::showFruit()
{
	scr.gotoxy(fruitCordX, fruitCordY);
	scr.set_col(scr.COLOR.at(fruitColor), scr.COLOR.at(fruitColor));

	std::cout << "  ";

	scr.gotoxy(119, 0);
}