#include "screen.h"

screen::screen() : colorFonConsole(11), colorField(10), colorFrame1(14), colorFrame2(8), colorSnake(1),
hout(GetStdHandle(STD_OUTPUT_HANDLE)) {}

void screen::set_col(color foreground, color background)
{
	SetConsoleTextAttribute(hout, ((short)background << 4) | (short)foreground);
}

void screen::gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void screen::paintFonConsole()
{
	set_col(COLOR.at(colorFonConsole), COLOR.at(colorFonConsole));
	
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 120; ++j)
		{
			if (i < 6 || i > 27 || j < 38 || j > 81)
			{
				gotoxy(j, i);
				std::cout << " ";
			}
		}
	}
}

void screen::paintField()
{
	for (int i = 0; i < field.getHeight(); ++i)
	{
		gotoxy(40, 7 + i);
		set_col(COLOR.at(colorField), COLOR.at(colorField));

		for (int j = 0; j < field.getWidth(); ++j)
			std::cout << " ";
		
		std::cout << std::endl;
	}
}

void screen::paintFieldFrame()
{
	int color = 0; 
	
	// risuen verhniuiy granitsu polya
	gotoxy(field.getFirstFieldPointX() - 2, field.getFirstFieldPointY() - 1);
	for (int i = 0; i < field.getWidth() + 4; ++i) 
	{
		if (color < 2)
			set_col(COLOR.at(colorFrame1), COLOR.at(colorFrame1)); 
		else
			set_col(COLOR.at(colorFrame2), COLOR.at(colorFrame2));

		std::cout << " ";

		++color;

		if (color > 3)
			color = 0;
	}

	for (int i = 0; i < field.getHeight(); ++i)
	{
		// risuen pravuiu granitsu polya
		gotoxy(field.getFirstFieldPointX() + field.getWidth(), field.getFirstFieldPointY() + i);
		
		if (i % 2 == 0)
			set_col(COLOR.at(colorFrame1), COLOR.at(colorFrame1));
		else
			set_col(COLOR.at(colorFrame2), COLOR.at(colorFrame2));

		std::cout << "  ";

		// risuen levuiu granitsu polya
		gotoxy(field.getFirstFieldPointX() - 2, field.getFirstFieldPointY() + i);

		if (i % 2 == 0)
			set_col(COLOR.at(colorFrame2), COLOR.at(colorFrame2));
		else
			set_col(COLOR.at(colorFrame1), COLOR.at(colorFrame1));

		std::cout << "  ";
	}

	// risuen nijniuiy granitsu polya
	gotoxy(field.getFirstFieldPointX() - 2, field.getHeight() + 7);
	for (int i = 0; i < field.getWidth() + 4; ++i)
	{
		if (color > 1)
			set_col(COLOR.at(colorFrame1), COLOR.at(colorFrame1));
		else
			set_col(COLOR.at(colorFrame2), COLOR.at(colorFrame2));

		std::cout << " ";

		++color;

		if (color > 3)
			color = 0;
	}

	gotoxy(0, 28);
}

void screen::inscriptionSnake()
{
	gotoxy(55, 3);

	if (colorFonConsole == 1)
	{
		set_col(color::white, COLOR.at(colorFonConsole));  // esli pole chernogo tsveta to vyvodim bukvy belogo tsveta
	}
	else
	{
		set_col(color::blue, COLOR.at(colorFonConsole));
	}

	std::cout << "S N A K E";
}

void screen::paintSnake()
{
	gotoxy(60, 9);
	if (colorSnake == colorField)
	{
		int tempColor = colorSnake + 1;

		if (tempColor == 16)
			tempColor = 0;

		set_col(COLOR.at(tempColor), COLOR.at(tempColor));
	}
	else
	{
		set_col(COLOR.at(colorSnake), COLOR.at(colorSnake));
	}

	std::cout << "      ";

	gotoxy(70, 9);
	if (colorField == 5)
	{
		set_col(COLOR.at(6), COLOR.at(6));
	}
	else
	{
		set_col(color::magenta, color::magenta);
	}
	
	std::cout << "  ";

	gotoxy(119, 0);
}

void screen::initialPage()
{
	paintFonConsole();
	inscriptionSnake();
	paintField();
	paintFieldFrame();
}

void screen::buttons(int& buttonIsPressed)
{
	gotoxy(120 / 2 - sms.at(0).length() / 2, 13);
	if (buttonIsPressed == 0)
		set_col(color::red, COLOR.at(colorField));
	else
	{
		if (colorField == 1)                             // esli knopka v tvet polya to menyaem tsvet knopki
		{
			set_col(color::lightgreen, COLOR.at(colorField));
		}
		else
		{
			set_col(color::blue, COLOR.at(colorField));
		}
	}
	std::cout << sms.at(0);

	gotoxy(120 / 2 - sms.at(1).length() / 2, 16);
	if (buttonIsPressed == 1)
		set_col(color::red, COLOR.at(colorField));
	else
	{
		if (colorField == 1)                             // esli knopka v tvet polya to menyaem tsvet knopki
		{
			set_col(color::lightgreen, COLOR.at(colorField));
		}
		else
		{
			set_col(color::blue, COLOR.at(colorField));
		}
	}
	std::cout << sms.at(1);

	gotoxy(120 / 2 - sms.at(2).length() / 2, 19);
	if (buttonIsPressed == 2)
		set_col(color::red, COLOR.at(colorField));
	else
	{
		if (colorField == 1)                                  // esli knopka v tvet polya to menyaem tsvet knopki
		{
			set_col(color::lightgreen, COLOR.at(colorField));
		}
		else
		{
			set_col(color::blue, COLOR.at(colorField));
		}
	}
	std::cout << sms.at(2);

	gotoxy(119, 0);
}

void screen::setColorFonConsole(int color) { colorFonConsole = color; }
void screen::setColorField(int color) { colorField = color; }
void screen::setColorFrame1(int color) { colorFrame1 = color; }
void screen::setColorFrame2(int color) { colorFrame2 = color; }

int screen::getColorFonConsole() { return colorFonConsole; }
int screen::getColorField() { return colorField; }
int screen::getColorFrame1() { return colorFrame1; }
int screen::getColorFrame2() { return colorFrame2; }
int screen::getColorSnake() { return colorSnake; }

void screen::screenName(int buttonIsPressed)
{
	clearStr();

	gotoxy(50, 16);
	if (colorField == 0)
	{
		set_col(color::white, COLOR.at(colorField));  // esli pole chernogo tsveta to vyvodim bukvy belogo tsveta
	}
	else
	{
		set_col(color::black, COLOR.at(colorField));
	}
	
	switch (buttonIsPressed)
	{
	case 0:                                    
		std::cout << sms.at(3);
		break;
	case 1:                                
		std::cout << sms.at(4);
		break;
	case 2:                                     
		std::cout << sms.at(5);
		break;
	case 3:                                   
		std::cout << sms.at(6);
		break;
	case 4:                                  
		std::cout << sms.at(7);
		break;
	}
}

void screen::clearStr(int i)
{
	set_col(COLOR.at(colorField), COLOR.at(colorField));

	if (i == 1)
	{
		gotoxy(50, 16);

		for (int i = 0; i < 14; ++i)
		{
			std::cout << " ";
		}
	}
	else
	{
		gotoxy(63, 16);

		std::cout << "      ";
	}
}

void screen::colorÑhoice(int checkColor)
{
	gotoxy(65, 16);
	set_col(COLOR.at(checkColor), COLOR.at(checkColor));
	std::cout << "  ";

	gotoxy(63, 16);
	set_col(COLOR.at(0), COLOR.at(colorField));
	std::cout << "< ";

	gotoxy(67, 16);
	set_col(COLOR.at(0), COLOR.at(colorField));
	std::cout << " >";
}

void screen::drawSeparatePartsOfTheScreen(int buttonIsPressed, int& checkColor)
{
	switch (buttonIsPressed)
	{
	case 0:
		colorField = checkColor;
		paintField();
		screenName(buttonIsPressed);
		paintSnake();
		break;
	case 1:
		colorFonConsole = checkColor;
		paintFonConsole();
		inscriptionSnake();
		break;
	case 2:
		colorFrame1 = checkColor;
		paintFieldFrame();
		break;
	case 3:
		colorFrame2 = checkColor;
		paintFieldFrame();
		break;
	case 4:
		colorSnake = checkColor;
		paintSnake();
		break;
	}
}