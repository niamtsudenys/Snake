#pragma once
#include <fstream>
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
	bool pause;

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

	bool input();

	// szadi zmei chistim pole
	void cleanTraces();

	// proveryaem esli novyi frukt ne poyavilsya v zmeike
	bool theCoordinatesOfTheFruitAreTheSameAsTheCoordinatesOfTheSnake();

	void saveScore();

	void comparóAllScore();
};