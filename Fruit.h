#pragma once
#include "screen.h"

class Fruit
{
private:
	int fruitCordX;
	int fruitCordY;
	int fruitColor;

	screen scr;
	std::vector <int> allColorFruit{ 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15 };

public:

	Fruit();

	int getColor();
	int getCordX();
	int getCordY();

	void setColor(int color);
	void setCordX(int fruitCordX);
	void setCordY(int fruitCordY);

	void addFruit(int colorField);
	void showFruit();
};