#include "game_progress.h"

game_progress::game_progress() : gameOver(false), buttonIsPressed(0), checkColor(0), play(false), 
lastTailCoordinateX(0), lastTailCoordinateY(0), pause(false) {}

void game_progress::show()
{
	srand(time(NULL));

	while (1)
	{
		initialPage();

		setup();

		logic();
	}
}

void game_progress::setup()
{
	while (!play)
	{
		int ch = 0;

		while (ch != 13)
		{
			buttons(buttonIsPressed);                  // risuem knopki

			paintSnake();                      

			ch = _getch();

			// knopki
			switch (ch)
			{
			case 's':                                   // s  vniz            
				++buttonIsPressed;
				break;
			case 'w':                                   // w  vverh           
				--buttonIsPressed;
				break;
			case 80:                                    //  vniz            
				++buttonIsPressed;
				break;
			case 72:                                    //  vverh           
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
	paintField();                                        // cistim pole ot knopok

	paintSnake();
	buttonIsPressed = 0;

	gotoxy(0, 0);
	set_col(color::blue, color::white);
	std::cout << buttonIsPressed;

	//  0 - pole
	//  1 - fon vocrug polya
	//  2 - ramka 1
	//  3 - ramka 2
	//  4 - nazvanie

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
			case 'd':                                     // s  vpravo           
				++buttonIsPressed;
				break;
			case 'a':                                     // w  vlevo          
				--buttonIsPressed;
				break;
			case 77:                                      //  vpravo            
				++buttonIsPressed;
				break;
			case 75:                                      //  vlevo          
				--buttonIsPressed;
				break;
			case 13:                                      //  enter         
				more = false;
				break;
			case 27:                                      //  esc       
				back = true;
				more = false;
				buttonIsPressed = 1;
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
			case 'd':                                     // s  vpravo          
				++checkColor;
				break;
			case 'a':                                     // w  vlevo          
				--checkColor;
				break;
			case 77:                                      //  vpravo           
				++checkColor;
				break;
			case 75:                                      //  vlevo          
				--checkColor;
				break;
			case 27:                                      //  esc  
				clearStr(2);
				more = false;
				checkColor = 0;
				break;
			case 13:                                      //  enter 
				drawSeparatePartsOfTheScreen(buttonIsPressed, checkColor);
				break;
			}

			if (checkColor > 15)
				checkColor = 0;
			else if (checkColor < 0)
				checkColor = 15;
		}
	}

	gotoxy(70, 26);                                     // stiraem nadpisy Esc - back
	std::cout << "          ";

	gotoxy(40, 26);                                     // stiraem nadpisy Enter - select
	std::cout << "              ";
}

void game_progress::logic()
{
	paintField();                                       // chistim pole

	navigation();                                       // podskazka po upravleniiu

	for (int i = 62; i >= 58; i -= 2)
		addSnake(getColorSnake(), i, 19, 0);            // sozdaem zmeyku na 3 yacheiki
	

	for (int i = snake.size() - 1; i >= 0; --i)         // risuem zmeiku s hvosta do golovy
		snake.at(i).showYourself();
	
	fruit.addFruit(getColorField());                    // generiruem frukt
    fruit.showFruit();                                  // risuem frukt

	liveScore(snake.size() - 3);                        // vyvodim resulitat v consoli

	switch (_getch())                                   // vnachale snake ne dvigaetsya
	{
	case 'w':                                           // pri najatii na 'w' zmeya nachinaet dvijenie vverh          
		snake.at(0).setDir(3);
		break;
	case 's':                                           // pri najatii na 's' zmeya nachinaet dvijenie vniz
		snake.at(0).setDir(2);
		break;                                          // vse krome 'w' i 's' eto dvijenie pryamo toesty vpravo
	}

	while (!gameOver)
	{
		liveScore(snake.size() - 3);                    // vyvodim resulitat v consoli v rejime online

		if (pause)
		{
			do
			{
				pause = false;
			} while (_getch() != 32);                   // snimaem pauzu toliko probelom
		}

		if (input())                                    // menyaem napravlenie dvijeniya
			break;                                      // esli vo vremya igry najali esc to konets igri
		
		cleanTraces();                                  // zametaem sledy za zmeikoy

		snakeCoordinateUpdate();                        // perezapisyvaem coord
		
		if ((snake.at(0).getCordX() > 38 && snake.at(0).getCordX() < 80) && (snake.at(0).getCordY() > 6 && snake.at(0).getCordY() < 27))
		{
			snake.at(0).showYourself();                 // risuem pervuiu yacheiku zmei tolyko esli ona nahoditsya v pole

			int speedSnake = 400 - snake.size() * 10;   // skorosti snake rastet po mere uvelicheniya dliny snake

			if (speedSnake == 49)                       // predel skorosty
				speedSnake = 50;

			Sleep(speedSnake);
		}
		
		// proverka esli zmeya siela frukt
		if (snake.at(0).getCordX() == fruit.getCordX() && snake.at(0).getCordY() == fruit.getCordY())
		{
			liveScore(snake.size() - 2);                 // vyvodim resulitat v consoli v rejime online
			
			do
			{
				fruit.addFruit(getColorField());         // generiruem frukt
			} while (theCoordinatesOfTheFruitAreTheSameAsTheCoordinatesOfTheSnake());

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

		// proveryaem esli zmeika udarilasi v stenku
		if ((snake.at(0).getCordX() == 38 || snake.at(0).getCordX() == 80) || (snake.at(0).getCordY() == 6 || snake.at(0).getCordY() == 27))
		{
			// izza togo chto snake vyshla za granitsu polya ee razmer na pole menishe na 1 yacheyku
			// i poetomu vostanavlivaem ee polnyi razmer v predelah polya
			gotoxy(lastTailCoordinateX, lastTailCoordinateY);          
			set_col(COLOR.at(getColorSnake()), COLOR.at(getColorSnake()));
			std::cout << "  ";

			// vostanavlivaem ramku
			paintFieldFrame();

			gameOver = true;
		}

		// proveryaem esli zmeika udarilasi v samu sebya
		for (int i = 3; i < snake.size(); ++i)
		{
			if (snake.at(0).getCordX() == snake.at(i).getCordX() && snake.at(0).getCordY() == snake.at(i).getCordY())
			{
				gameOver = true;
			}
		}
	}

	if (gameOver)
	{
		comparóAllScore();
		saveScore();
		
		play = false;
		snake.clear();
		gameOver = false;

		if (getColorField() != 4)
			set_col(COLOR.at(4), COLOR.at(getColorField()));
		else
			set_col(COLOR.at(2), COLOR.at(getColorField()));

		gotoxy(120 / 2 - getSms(8).length() / 2, 14);
		std::cout << getSms(8);

		if (getColorField() != 0)
			set_col(COLOR.at(0), COLOR.at(getColorField()));
		else
			set_col(COLOR.at(15), COLOR.at(getColorField()));
		
		gotoxy(120 / 2 - getSms(9).length() / 2, 16);
		std::cout << getSms(9);

		gotoxy(119, 0);

		int ch = _getch();
	}
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

bool game_progress::input()
{
	if (_kbhit())
	{
		int ch = _getch();

		switch (ch)
		{
		case 'd':
			if (snake.at(0).getDir() != 1)
				snake.at(0).setDir(0);                           // povarachivaem vpravo esli povorot ne na 180
			break;
		case 'a':
			if (snake.at(0).getDir() != 0)
				snake.at(0).setDir(1);                          // povarachivaem vlevo esli povorot ne na 180
			break;
		case 's':
			if (snake.at(0).getDir() != 3) 
				snake.at(0).setDir(2);                          // povarachivaem vniz esli povorot ne na 180
			break;
		case 'w':
			if (snake.at(0).getDir() != 2)
				snake.at(0).setDir(3);                          // povarachivaem vverh esli povorot ne na 180
			break;
		case 27:                                                // esc / vyhod iz igry v meniu
			gameOver = true;
			break;
		case 32:
			pause = true;                                      // probel / stavim igru na pauzu
			break;
		}
	}

	return gameOver;
}

void game_progress::cleanTraces()
{
	// risuem szadi zmeiki pole
	if (snake.at(0).getCordX() > 38 && snake.at(0).getCordX() < 80 && snake.at(0).getCordY() > 6 && snake.at(0).getCordY() < 27)
	{
		gotoxy(snake.at(snake.size() - 1).getCordX(), snake.at(snake.size() - 1).getCordY());
		set_col(COLOR.at(getColorField()), COLOR.at(getColorField()));
		std::cout << "  ";

		// sohranyaem posledniiu kotoruiu pochistili
		lastTailCoordinateX = snake.at(snake.size() - 1).getCordX();
		lastTailCoordinateY = snake.at(snake.size() - 1).getCordY();
	}
	else // esli tochka byla ne v pole to vostanavlivaem ramku
		paintFieldFrame();
}

bool game_progress::theCoordinatesOfTheFruitAreTheSameAsTheCoordinatesOfTheSnake()
{
	int fruitInside = false;

	for (int i = 0; i < snake.size(); ++i)
	{
		if (fruit.getCordX() == snake.at(i).getCordX() && fruit.getCordY() == snake.at(i).getCordY())
		{
			fruitInside = true;
			break;
		}
	}
	
	return fruitInside;
}

void game_progress::saveScore()
{
	std::fstream fs;

	std::string path = "score.txt";

	fs.open(path, std::fstream::out | std::fstream::app);
	
	// esli fail otkrylsya to sohranyaem danye v file
	if (fs.is_open())                                
		fs << (snake.size() - 3) << std::endl;        

	fs.close();
}

void game_progress::comparóAllScore()
{
	std::fstream fs;

	std::string path = "score.txt";

	int temp = 0;                            // peremenaya v kotoroy budem hranity znachenie iz file
	bool record = true;
	
	fs.open(path, std::fstream::in);
	
	// esli fail otkrylsya znachit scityvaem danie iz file i sravnivaem ih mejdu soboi
	if (fs.is_open())
	{
		while (!fs.eof())
		{
			fs >> temp;                      // scityvaem iz faila znacheniya po ocheredi

			if (temp >= (snake.size() - 3))  // esli v faile naidetsya znachenie bolyshe to nashe znachenie ne rekord
			{
				record = false;
				break;
			}
		}
	}

	getRecordScore((snake.size() - 3), record);  // vyvod konechinogo rezulitata v console

	fs.close();
}