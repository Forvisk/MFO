#include "trem.h"

Trem::Trem( vector<Point> & ps){
    cout << "trem ini" << endl;
    srand( time(nullptr));
    pAtual = 0;
    pProximo = 1;
    pos.x = ps[0].x;
    pos.y = ps[0].y;
    vecP = ps;
    veloc.x = 0;
    veloc.y = 0;
    acel.x = 0;
    acel.y = 0;
    taxaAcel = 0;
    cout << "trem fim" << endl;
}

void Trem::setPos( int px, int py){
    pos.x = px;
    pos.y = py;
}

void Trem::getPos( int *x, int *y){
    *x = pos.x;
    *y = pos.y;
}

void Trem::moveTrem(){
    int seAcel = rand() % 3;
    float taxaX = ( vecP[ pProximo].x - vecP[ pAtual].x)/20;
    float taxaY = ( vecP[ pProximo].y - vecP[ pAtual].y)/20;
    //veloc.x = (vecP[pProximo].x - vecP[pAtual].x);
    //veloc.y = (vecP[pProximo].y - vecP[pAtual].y);

    if (( vecP[ pProximo].x - vecP[ pAtual].x) > 0)
    {
        acel.x = 1;
    }
    else
    {
        acel.x = -1;
    }

    if (( vecP[ pProximo].y - vecP[ pAtual].y) > 0)
    {
        acel.y = 1;
    }
    else if (( vecP[ pProximo].y - vecP[ pAtual].y) < 0)
    {
        acel.y = -1;
    }
    else
        acel.y = 0;

    switch (seAcel) {
        case 0: // acelera
            
        case 1: // desacelera

    }

    cout << "Velocidade trem: " << veloc.x << ", " << veloc.y << endl;
    cout << "Aceleracao trem: " << acel.x << ", " << acel.y << endl;

    this->moveBasico();
}

void Trem::moveBasico(){
    pos.x = vecP[pProximo].x;
    pos.y = vecP[pProximo].y;
    pAtual = pProximo;
    pProximo++;
    if (pProximo >= vecP.size())
        pProximo = 0;
}

void Trem::moveAcel(){
    pos.x
}
