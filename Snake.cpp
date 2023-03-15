#include "Snake.h"

Snake::Snake() : dir(0), cordX(0), cordY(0), color(0) {}
Snake::Snake(int dir, int cordX, int cordY, int color) : dir(dir), cordX(cordX), cordY(cordY), color(color) {}

int Snake::getDir() { return dir; }
int Snake::getCordX() { return cordX; }
int Snake::getCordY() { return cordY; }

void Snake::setDir(int dir) { this->dir = dir; }
void Snake::setCordX(int cordX) { this->cordX = cordX; }
void Snake::setCordY(int cordY) { this->cordY = cordY; }

void Snake::showYourself()
{
	s.gotoxy(cordX, cordY);

	s.set_col(s.COLOR.at(color), s.COLOR.at(color));

	std::cout << "SS";

	s.gotoxy(119, 0);
}