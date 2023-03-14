#include "game_progress.h"

game_progress::game_progress() : gameOver(false), buttonIsPressed(0), checkColor(0), play(false), 
lastTailCoordinateX(0), lastTailCoordinateY(0) {}

void game_progress::show()
{
	srand(time(NULL));
	
	initialPage();

	setup();
	/////////
	logic();
}

void game_progress::setup()
{
	while (!play)
	{
		int ch = 0;

		while (ch != 13)
		{
			buttons(buttonIsPressed);
			paintSnake();

			ch = _getch();

			// knopki
			switch (ch)
			{
			case 's':                          // s  vniz            
				++buttonIsPressed;
				break;
			case 'w':                          // w  vverh           
				--buttonIsPressed;
				break;
			case 80:                           //  vniz            
				++buttonIsPressed;
				break;
			case 72:                           //  vverh           
				--buttonIsPressed;
				break;
			}

			if (buttonIsPressed < 0)
				buttonIsPressed = 2;
			else if (buttonIsPressed > 2)
				buttonIsPressed = 0;
		}

		if (buttonIsPressed == 0)
			play = true;
		else if (buttonIsPressed == 1)
			setting();
		else if (buttonIsPressed == 2)
			exit(0);
	}
}

void game_progress::setting()
{
	paintField();   // cistim pole ot knopok

	paintSnake();
	buttonIsPressed = 0;

	gotoxy(0, 0);
	set_col(color::blue, color::white);
	std::cout << buttonIsPressed;

	// 0 - pole
	// 1 - fon vocrug polya
	// 2 - ramka 1
	// 3 - ramka 2
	// 4 - nazvanie

	bool back = false;

	while (true)
	{
		bool more = true;

		while (more)
		{
			screenName(buttonIsPressed);

			int ch = _getch();

			switch (ch)
			{
			case 'd':                          // s  vpravo           
				++buttonIsPressed;
				break;
			case 'a':                          // w  vlevo          
				--buttonIsPressed;
				break;
			case 77:                           //  vpravo            
				++buttonIsPressed;
				break;
			case 75:                           //  vlevo          
				--buttonIsPressed;
				break;
			case 13:                           //  enter         
				more = false;
				break;
			case 27:                           //  esc       
				back = true;
				more = false;
				clearStr();
				break;
			}

			if (buttonIsPressed > 4)
				buttonIsPressed = 4;
			else if (buttonIsPressed < 0)
				buttonIsPressed = 0;
		}

		if (back)
			break;

		more = true;

		while (more)
		{
			colorÑhoice(checkColor);

			int ch = _getch();

			switch (ch)
			{
			case 'd':                          // s  vpravo          
				++checkColor;
				break;
			case 'a':                          // w  vlevo          
				--checkColor;
				break;
			case 77:                           //  vpravo           
				++checkColor;
				break;
			case 75:                           //  vlevo          
				--checkColor;
				break;
			case 27:                           //  esc  
				clearStr(2);
				more = false;
				checkColor = 0;
				break;
			case 13:                           //  enter 
				drawSeparatePartsOfTheScreen(buttonIsPressed, checkColor);
				break;
			}

			if (checkColor > 15)
				checkColor = 0;
			else if (checkColor < 0)
				checkColor = 15;
		}
	}
}

void game_progress::logic()
{
	paintField();                                       // chistim pole

	for (int i = 62; i >= 58; i -= 2)
		addSnake(getColorSnake(), i, 19, 0);            // sozdaem zmeyku na 3 yacheiki
	

	for (int i = snake.size() - 1; i >= 0; --i)         // risuem zmeiku s hvosta do golovy
		snake.at(i).showYourself();
	
	fruit.addFruit(getColorField());                    // generiruem frukt
    fruit.showFruit();                                  // risuem frukt

	while (!gameOver)
	{
		input();                                        // menyaem napravlenie dvijeniya
		
		cleanTraces();                                  // zametaem sledy za zmeikoy

		snakeCoordinateUpdate();                        // perezapisyvaem coord
		
		snake.at(0).showYourself();                     // risuem pervuiu yacheiku zmei tolyko esli ona nahoditsya v pole

		if (snake.at(0).getCordX() >= 40 && snake.at(0).getCordX() <= 78 && snake.at(0).getCordY() >= 7 && snake.at(0).getCordY() <= 26)
		{
			
		}
		
		Sleep(100);

		// proverka esli zmeya siela frukt
		if (snake.at(0).getCordX() == fruit.getCordX() && snake.at(0).getCordY() == fruit.getCordY())
		{
			fruit.addFruit(getColorField());             // generiruem frukt
			fruit.showFruit();                           // risuem frukt
			
			// smotrim napravlenie hvosta i dobavlyaem yacheiku szadi
			switch (snake.at(snake.size() - 1).getDir())       
			{
			case 0:                                      // s  vpravo          
				addSnake(getColorField(), snake.at(snake.size() - 1).getCordX() - 1, snake.at(snake.size() - 1).getCordY(), 0);
					break;
			case 1:                                      // w  vlevo          
				addSnake(getColorField(), snake.at(snake.size() - 1).getCordX() + 1, snake.at(snake.size() - 1).getCordY(), 0);
				break;
			case 2:                                      //  vniz          
				addSnake(getColorField(), snake.at(snake.size() - 1).getCordX(), snake.at(snake.size() - 1).getCordY() - 1, 0);
				break;
			case 3:                                      //  vverh          
				addSnake(getColorField(), snake.at(snake.size() - 1).getCordX(), snake.at(snake.size() - 1).getCordY() + 1, 0);
				break;
			}
		}

		// proveryaem esli zmeika ne udarilasi v stenku
		if ((snake.at(0).getCordX() == 38 || snake.at(0).getCordX() == 80) || (snake.at(0).getCordY() == 6 || snake.at(0).getCordY() == 27))
		{
			gameOver = true;
		}

		// proveryaem esli zmeika ne udarilasi v sebya
		for (int i = 3; i < snake.size(); ++i)
		{
			if (snake.at(0).getCordX() == snake.at(i).getCordX() && snake.at(0).getCordY() == snake.at(i).getCordY())
			{
				gameOver = true;
			}
		}
	}

	gameOver = false;
}

void game_progress::addSnake(int color, int coordX, int coordY, int dir)
{
	Snake tempSnake(dir, coordX, coordY, color);
	snake.push_back(tempSnake);
}

void game_progress::snakeCoordinateUpdate()
{
	for (int i = snake.size() - 1; i >= 0; --i)            
	{
		if (i > 0)
		{
			snake.at(i).setCordX(snake.at(i - 1).getCordX());     // v posledniuiu yacheiku zmei priraravnivaem s predposledney i tak dalyshe
			snake.at(i).setCordY(snake.at(i - 1).getCordY());
			snake.at(i).setDir(snake.at(i - 1).getDir());
		}
		else
		{
			switch (snake.at(i).getDir())                         // pervoy yaceike prisvaivaem sleduiuchie coordinaty v danom napravlenii
			{
			case 0:                                               // vpravo          
				snake.at(i).setCordX(snake.at(i).getCordX() + 2); 
				break;
			case 1:                                               // vlevo          
				snake.at(i).setCordX(snake.at(i).getCordX() - 2);
				break;
			case 2:                                               // vniz          
				snake.at(i).setCordY(snake.at(i).getCordY() + 1);
				break;
			case 3:                                               // vverh         
				snake.at(i).setCordY(snake.at(i).getCordY() - 1);
				break;
			}
		}
	}
}

void game_progress::input()
{
	if (_kbhit())
	{
		int ch = _getch();

		switch (ch)
		{
		case 'd':
			snake.at(0).setDir(0);   // povarachivaem vpravo
			break;
		case 77:
			snake.at(0).setDir(0);
			break;
		case 'a':
			snake.at(0).setDir(1);   // povarachivaem vlevo
			break;
		case 75:
			snake.at(0).setDir(1);
			break;
		case 's':
			snake.at(0).setDir(2);   // povarachivaem vniz
			break;
		case 80:
			snake.at(0).setDir(2);
			break;
		case 'w':
			snake.at(0).setDir(3);   // povarachivaem vverh
			break;
		case 72:
			snake.at(0).setDir(3);
			break;
		}
	}
}

void game_progress::cleanTraces()
{
	// risuem szadi zmeiki pole
	gotoxy(snake.at(snake.size() - 1).getCordX(), snake.at(snake.size() - 1).getCordY()); 
	set_col(COLOR.at(getColorField()), COLOR.at(getColorField()));
	std::cout << "  ";
}
