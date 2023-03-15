#include "field.h"


Field::Field() : height(20), width(40), firstFieldPointX(40), firstFieldPointY(7) {}

int Field::getHeight() { return height; }

int Field::getWidth() { return width; }

int Field::getFirstFieldPointX() { return firstFieldPointX; }

int Field::getFirstFieldPointY() { return firstFieldPointY; }