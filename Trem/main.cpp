#include <iostream>
#include "class/mapatrem.h"
#include "class/threads/thread.h"
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    MapaTrem trens;

    // posições para os trens
    vector<Point> pt1;
    pt1.push_back(Point(25, 158));//Lucerne
    pt1.push_back(Point(67, 158));//a1
    pt1.push_back(Point(180, 158));//b1
    pt1.push_back(Point(304, 242));//Stans
    pt1.push_back(Point(435, 242));//c
    pt1.push_back(Point(475, 242));//Engelberg

    vector<Point> pt2;
    pt2.push_back(Point(25, 326));//Sarnen
    pt2.push_back(Point(67, 326));//a2
    pt2.push_back(Point(180, 326));//b2
    pt2.push_back(Point(304, 242));//Stans
    pt2.push_back(Point(435, 242));//c
    pt2.push_back(Point(475, 242));//Engelberg

    //trens.Trem1Pos(200,200);
    //trens.Trem2Pos(100,200);
    //trens.Trem1Txt("Mensagem trem 1.");
    //trens.Trem2Txt("Mensagem trem 2.");

    trens.Gate(1);
    for(Point p : pt1)
    {
        trens.Trem1Pos(p.x,p.y);
        Thread::SleepMS(3000);

        int key = trens.GetLastKey();
        cout << "LastKey = " << key << endl;
        if(key == 27)
            return 1;
    }

    trens.Gate(0);
    for(Point p : pt2)
    {
        trens.Trem2Pos(p.x,p.y);
        Thread::SleepMS(3000);

        int key = trens.GetLastKey();
        cout << "LastKey = " << key << endl;
        if(key == 27) //esc = 27
            return 1;
    }

    return 0;
}
