#pragma once
#include "screen.h"

class Snake
{
private:

	int dir;
	int cordX;
	int cordY;
	int color;

	screen s;

public:

	Snake();
	Snake(int dir, int cordX, int cordY, int color);

	int getDir();
	int getCordX();
	int getCordY();

	void setDir(int dir);
	void setCordX(int cordX);
	void setCordY(int cordY);

	void showYourself();
};