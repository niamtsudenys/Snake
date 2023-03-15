#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include "field.h"

class screen
{
private:

    int colorFonConsole;
    int colorField;
    int colorFrame1;
    int colorFrame2;
    int colorSnake;

    Field field;
    HANDLE hout;

    std::vector<std::string> sms
    {
        "Play", "Setting", "Exit", "Field >", "< Fon >", "< Frame 1 >", "< Frame 2 >", "< Snake", "Game over!", "press any key to continue",
        "Your new record: ", "Your result: ", "Score: "
    };

public:
    
    screen();

    enum class color
    {
        black, blue, green, cyan, red, magenta, brown, lightgray, darkgray,
        lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white
    };

    std::vector<color> COLOR  // dlya funk SETCOLOR()
    { 
        color::black, color::blue, color::green, color::cyan, color::red, color::magenta, color::brown, color::lightgray, color::darkgray,
        color::lightblue, color::lightgreen, color::lightcyan, color::lightred, color::lightmagenta, color::yellow, color::white
    };  

    void gotoxy(int x, int y);
    void set_col(color foreground, color background);
  
    void paintFonConsole();                                         
    void paintField();
    void paintFieldFrame();
    void inscriptionSnake();
    void paintSnake();

    void initialPage();

    void buttons(int& buttonIsPressed);

    void setColorFonConsole(int color);
    void setColorField(int color);
    void setColorFrame1(int color);
    void setColorFrame2(int color);

    int getColorFonConsole();
    int getColorField();
    int getColorFrame1();
    int getColorFrame2();
    int getColorSnake();
    std::string getSms(int index);

    void screenName(int buttonIsPressed);
    void clearStr(int i = 1);
    void colorСhoice(int checkColor);
    void drawSeparatePartsOfTheScreen(int buttonIsPressed, int& checkColor);

    void navigation();

    void liveScore(int score);
    void getRecordScore(int score, bool record);
};