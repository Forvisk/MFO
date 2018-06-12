
#ifndef TREM_H
#define TREM_H

#include <cstdlib>
#include <ctime>
#include "mapatrem.h"

using namespace std;

class Trem{
protected:
    Thread *thread = NULL;

    Point pos;
    Point veloc;
    Point acel;
    unsigned int taxaAcel;
    unsigned int pAtual;
    unsigned int pProximo;
    vector<Point> vecP;
    void moveAcel();
public:
    Trem( vector<Point> & ps);
    void setPos( int px, int py);
    void getPos( int *x, int *y);
    void moveTrem();
    void moveBasico();
};

#endif
