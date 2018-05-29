
#ifndef TREM_H
#define TREM_H

#include "mapatrem.h"

using namespace std;

class Trem{
protected:
    Thread *thread = NULL;
    MapaTrem mapa;

    Point pos;
    unsigned int pAtual;

    int velX;
    int velY;
    int acelX;
    int acelY;
    vector<Point> vecP;
public:
    Trem( MapaTrem & nMapa, vector<Point> & ps);
    void getMapa( MapaTrem & nMapa);
    void setPos( int px, int py);
    void posAtual( int *x, int *y);
    void moveTrem();
};

#endif
