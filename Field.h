#pragma once

class Field
{
private:

	int height;
	int width;

	int firstFieldPointX;
	int firstFieldPointY;

public:

	Field();

	int getHeight();

	int getWidth();

	int getFirstFieldPointX();

	int getFirstFieldPointY();
};