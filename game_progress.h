#pragma once
#include "screen.h"
#include "Snake.h"
#include "Fruit.h"

class game_progress : public screen
{
private:
	bool gameOver;
	int buttonIsPressed;
	int checkColor;
	bool play;
	int lastTailCoordinateX;
	int lastTailCoordinateY;

	std::vector<Snake> snake;
	Fruit fruit;

public:

	game_progress();

	void show();
	
	void setup();

	void setting();

	void logic();

	void addSnake(int color, int coordX, int coordY = 19, int dir = 0);

	// zmeya delaet shag
	void snakeCoordinateUpdate();

	void input();

	// szadi zmei chistim pole
	void cleanTraces();
};