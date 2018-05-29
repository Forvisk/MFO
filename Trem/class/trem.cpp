#include "trem.h"

Trem::Trem( MapaTrem & nMapa, vector<Point> & ps){
    cout << "trem x" << endl;
    pos.x = ps[0].x;
    pos.y = ps[0].y;
    pAtual = 0;
    mapa = nMapa;
    vecP = ps;
    cout << "trem y" << endl;
    thread = new Thread();
    thread->Event((Task *) this);
    cout << "trem z" << endl;
}

void Trem::getMapa( MapaTrem & nMapa){
    mapa = nMapa;
}

void Trem::setPos( int px, int py){
    pos.x = px;
    pos.y = py;
}

void Trem::posAtual( int *x, int *y){
    *x = pos.x;
    *y = pos.y;
}

void Trem::moveTrem(){
    pAtual++;
    if( pAtual >= vecP.size())
        pAtual = 0;
    mapa.Trem1Pos( vecP[pAtual].x, vecP[pAtual].y);
    Thread::SleepMS(2000);
}
