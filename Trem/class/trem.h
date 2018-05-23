#ifndef TREM_H
#define TREM_H
#include <string>
#include <iostream>

using namespace std;

class Trem : public Task{
protected:
  int posX;
  int posY;

  int velX;
  int velY;
  int acelX;
  int acelY;
  std::vector<Point> vecP;
}
