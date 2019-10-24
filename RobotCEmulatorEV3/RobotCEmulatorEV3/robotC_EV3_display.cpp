#include "stdafx.h"

#include "robotC_EV3_display.h"

namespace RobotC
{
namespace Ev3
{
namespace Impl
{

char screen[ScreenSize];
char overflowPixel = 0;
bool initialized = false;

char& pixel(int x, int y)
{
  if (!initialized)
  {
    eraseDisplay();
    initialized = true;
  }

  if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight)
    return overflowPixel;

  return screen[x + y * ScreenWidth];
}

//inline void printScreen()
//{
//  for (int x = 0; x < ScreenWidth + 2; ++x)
//  {
//    std::cout << '-';
//  }
//  std::cout << std::endl;
//
//  for (int y = ScreenHeight - 1; y >= 0; --y)
//  {
//    std::cout << '|';
//
//    for (int x = 0; x < ScreenWidth; ++x)
//    {
//      const char output = (pixel(x, y) != 0) ? char(219) : ' ';
//      std::cout << output;
//    }
//    std::cout << '|' << std::endl;
//  }
//  for (int x = 0; x < ScreenWidth + 2; ++x)
//  {
//    std::cout << '-';
//  }
//}
}
}
}


namespace RobotC
{
namespace Ev3
{

void eraseDisplay()
{
  memset(Impl::screen, 0, ScreenSize);
}


void setPixel(int x, int y)
{
  Impl::pixel(x, y) = 1;
}

void clearPixel(int x, int y)
{
  Impl::pixel(x, y) = 0;
}

void drawRect(int left, int top, int right, int bottom)
{
  for (int y = bottom; y <= top; ++y)
  {
    setPixel(left, y);
    setPixel(right, y);
  }
  for (int x = left; x <= right; ++x)
  {
    setPixel(x, top);
    setPixel(x, bottom);
  }
}

void fillRect(int left, int top, int right, int bottom)
{
  for (int y = bottom; y <= top; ++y)
  {
    for (int x = left; x <= right; ++x)
    {
      setPixel(x, y);
    }
  }
}

void drawLine(int xPos, int yPos, int xPosTo, int yPosTo)
{
  const int dx = xPosTo - xPos;
  const int dy = yPosTo - yPos;
  if (dx == 0 && dy == 0)
  {
    setPixel(xPos, yPos);
    return;
  }

  if (abs(dx) < abs(dy))
  {
    const int iy = Impl::sign(dy);
    const double k = double(dx) / double(dy);
    for (int y = yPos; y != yPosTo + iy; y += iy)
    {
      const int x = xPos + int(round(k * (y - yPos)));
      setPixel(x, y);
    }
  }
  else
  {
    const int ix = Impl::sign(dx);
    const double k = double(dy) / double(dx);
    for (int x = xPos; x != xPosTo + ix; x += ix)
    {
      const int y = yPos + int(round(k * (x - xPos)));
      setPixel(x, y);
    }
  }
}

}
}