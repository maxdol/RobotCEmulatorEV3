#pragma once

#include <iostream>

namespace RobotC
{
namespace Ev3
{

// constants and globals
int const ScreenWidth = 178;
int const ScreenHeight = 128;
int const ScreenSize = ScreenWidth * ScreenHeight;

////////////////////////////////////////////
/// public API /////////////////////////////
////////////////////////////////////////////
void eraseDisplay();
void setPixel(int x, int y);
void clearPixel(int x, int y);
void drawRect(int left, int top, int right, int bottom);
void fillRect(int left, int top, int right, int bottom);
void drawLine(int xPos, int yPos, int xPosTo, int yPosTo);
void printScreen();

}
}

namespace RobotC
{
namespace Ev3
{
namespace Impl
{

int const ScreenRatio = 4;

extern char screen[ScreenSize];
extern char overflowPixel;
extern bool initialized;

char& pixel(int x, int y);

inline int sign(int x)
{
  return x == 0 ? 0 :
    x > 0 ? 1
    : -1;
}

}
}
}


////////////////////////////////////////////
/// util implementation ////////////////////
////////////////////////////////////////////

