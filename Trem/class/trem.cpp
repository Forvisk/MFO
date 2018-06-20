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
    inicio = true;

    cout << "trem fim" << endl;
}

void Trem::setPos( int px, int py){
    pos.x = px;
    pos.y = py;
}

bool Trem::getInicio(){
    return inicio;
}

void Trem::getPos( int *x, int *y){
    *x = pos.x;
    *y = pos.y;
}

void Trem::moveTrem(){
    inicio = false;
    this->moveBasico();
}

void Trem::moveBasico(){
    pos.x = vecP[pProximo].x;
    pos.y = vecP[pProximo].y;
    pAtual = pProximo;
    pProximo++;
    if (pProximo >= vecP.size()){
        pProximo = 0;
        inicio = true;
    }
}
