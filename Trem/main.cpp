#include <iostream>
#include "class/mapatrem.h"
#include "class/trem.h"
#include "class/threads/thread.h"
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
    MapaTrem trens;
    //Trem trem1;
    //Trem trem2;
    int x, y;

    // posições para os trens
    vector<Point> pt1;
    pt1.push_back(Point(25, 158));//Lucerne
    pt1.push_back(Point(67, 158));//a1
    pt1.push_back(Point(180, 158));//b1
    pt1.push_back(Point(304, 242));//Stans
    pt1.push_back(Point(435, 242));//c
    pt1.push_back(Point(475, 242));//Engelberg
    pt1.push_back(Point(435, 242));//c
    pt1.push_back(Point(304, 242));//Stans
    pt1.push_back(Point(180, 158));//b1
    pt1.push_back(Point(67, 158));//a1
    pt1.push_back(Point(25, 158));//Lucerne

    vector<Point> pt2;
    pt2.push_back(Point(25, 326));//Sarnen
    pt2.push_back(Point(67, 326));//a2
    pt2.push_back(Point(180, 326));//b2
    pt2.push_back(Point(304, 242));//Stans
    pt2.push_back(Point(435, 242));//c
    pt2.push_back(Point(475, 242));//Engelberg
    pt2.push_back(Point(435, 242));//c
    pt2.push_back(Point(304, 242));//Stans
    pt2.push_back(Point(180, 326));//b2
    pt2.push_back(Point(67, 326));//a2
    pt2.push_back(Point(25, 326));//Sarnen

    //trens.Trem1Pos(200,200);
    //trens.Trem2Pos(100,200);
    //trens.Trem1Txt("Mensagem trem 1.");
    //trens.Trem2Txt("Mensagem trem 2.");
    Trem trem1 = Trem( pt1);
    cout << "here" << endl;
    Trem trem2 = Trem( pt2);
    cout << "here 2" << endl;
    //trens.Gate(1);
    while(true)
    {
        Thread::SleepMS(1000);
        trem1.getPos( &x, &y);
        cout << "Trem 1 : ( " << x << ", " << y << ")" << endl;
        trens.Trem1Pos( x, y);

        trem2.getPos( &x, &y);
        cout << "Trem 2 : ( " << x << ", " << y << ")" << endl;
        trens.Trem2Pos( x, y);

        int key = trens.GetLastKey();
        cout << "LastKey = " << key << endl;
        if(key == 27)
            return 1;

        trem1.moveTrem();
        trem2.moveTrem();
    }



    //trens.Gate(0);
    /*
    for( Point p : pt2){
        trens.Trem2Pos(p.x,p.y);
        Thread::SleepMS(2000);

        int key = trens.GetLastKey();
        cout << "LastKey = " << key << endl;
        if(key == 27) //esc = 27
            return 1;
    }
    */

    return 0;
}
