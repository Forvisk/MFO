/*
 * It shows the map of the train problem (for petri nets)
 * Copyright (C) 2018  rafaelberri@gmail.com rafaelberri@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mapatrem.h"

MapaTrem::MapaTrem()
{
    fundoG1 = imread("img/mapa1.png", CV_LOAD_IMAGE_COLOR);   // Read the file
    fundoG0 = imread("img/mapa2.png", CV_LOAD_IMAGE_COLOR);   // Read the file
    trem1 = imread("img/train1.png", CV_LOAD_IMAGE_COLOR);
    trem2 = imread("img/train2.png", CV_LOAD_IMAGE_COLOR);
    
    thread = new Thread();
    thread->Event((Task *) this);
}

MapaTrem::~MapaTrem()
{
    //if(dLastKey != NULL)
    //    delete dLastKey;
    
    if(thread != NULL)
        delete thread;
}

int MapaTrem::Gate()
{
    int g;
    sMapa.Lock();
    g = gate;
    sMapa.Unlock();
    
    return g;
}

bool MapaTrem::Gate(int position)
{
    if(position > 1 || position < 0)
        return false;
    
    sMapa.Lock();
    gate=position;
    sMapa.Unlock();
    
    return true;
}

int MapaTrem::GetLastKey()
{
    int l = 0;
    sMapa.Lock();
    l = lastKey;
    sMapa.Unlock();
    
    return l;
}

int MapaTrem::GetLastKeyAndEmpty()
{
    int l = 0;
    sMapa.Lock();
    l = lastKey;
    lastKey = -1;
    sMapa.Unlock();
    
    return l;
}

bool MapaTrem::Trem1Pos(int x, int y)
{
    int w = this->Width();
    int h = this->Height();
    
    if(x < 0 || x >= w || y < 0 || y >= h)
    {
        return false;
    }
    
    sMapa.Lock();
    t1x = x;
    t1y = y;
    sMapa.Unlock();
    
    return true;
}

void MapaTrem::GetTrem1Pos(int* x, int* y)
{
    sMapa.Lock();
    *x = t1x;
    *y = t1y;
    sMapa.Unlock();
}

void MapaTrem::Trem1Txt(string mensagem)
{
    sMapa.Lock();
    t1msg = mensagem;
    sMapa.Unlock();
}

bool MapaTrem::Trem2Pos(int x, int y)
{
    int w = this->Width();
    int h = this->Height();
    
    if(x < 0 || x >= w || y < 0 || y >= h)
    {
        return false;
    }
    
    sMapa.Lock();
    t2x = x;
    t2y = y;
    sMapa.Unlock();
    
    return true;
}

void MapaTrem::Trem2Txt(string mensagem)
{
    sMapa.Lock();
    t2msg = mensagem;
    sMapa.Unlock();
}

void MapaTrem::GetTrem2Pos(int* x, int* y)
{
    sMapa.Lock();
    *x = t2x;
    *y = t2y;
    sMapa.Unlock();
}

int MapaTrem::Height()
{
    int h;
    sMapa.Lock();
    h = fundoG0.rows;
    sMapa.Unlock();
    
    return h;
}

int MapaTrem::Width()
{
    int w;
    sMapa.Lock();
    w = fundoG0.cols;
    sMapa.Unlock();
    
    return w;
}

bool MapaTrem::imgAdd(cv::Mat &fundo, cv::Mat &add, int x, int y, Vec3b transpColor)
{
    Vec3b *pixel;
    Rect local;
    
    local.width = add.cols;
    local.height = add.rows;
    local.x = x - local.width / 2;
    local.y = y - local.height / 2;
    
    if(local.x < 0 ||
        local.y < 0 ||
        fundo.cols < local.x + local.width ||
        fundo.rows < local.y + local.height)
        return false;
    
    for (int i = 0; i < add.rows; i++)
    {
        for (int j = 0; j < add.cols; j++)
        {
            pixel = add.ptr<Vec3b>(j, i);
            
            if(*pixel != transpColor)
                fundo.at<Vec3b>(Point(i + local.x, j + local.y)) = *pixel;
        }
    }
    
    return true;
}



// Task
bool MapaTrem::Exec()
{
    while(1)
    {
        Mat img;
        
        if(this->Gate() == 0)
        {
            sMapa.Lock();
            img = fundoG0.clone();
            sMapa.Unlock();
        }
        else
            img = fundoG1.clone();
        
        int x, y;
        string msg;
        
        // trem 1
        sMapa.Lock();
        x = t1x;
        y = t1y;
        msg = t1msg;
        sMapa.Unlock();
        imgAdd(img, trem1, x, y, Vec3b(255,255,255));
        
        if(msg != "")
            draw::text(msg, &img, Point(10,50), Scalar::all(0), 1);
        
        // trem 2
        sMapa.Lock();
        x = t2x;
        y = t2y;
        msg = t2msg;
        sMapa.Unlock();
        imgAdd(img, trem2, x, y, Vec3b(255,255,255));
        
        if(msg != "")
            draw::text(msg, &img, Point(10,450), Scalar::all(0), 1);
        
        imshow( "Trens", img);
        int key = waitKey(1);
        
        if(key != -1)
        {
            sMapa.Lock();
            lastKey = key;
            sMapa.Unlock();
        }
    }
    
    return true;
}

