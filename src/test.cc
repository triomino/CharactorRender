#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <utility>
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "rasterizer.h"
#include "fragment.h"
#include "vertex.h"
#include "my_math.h"
using namespace std;

#define width 79
#define height 40

void line();

int main(){
    line();
}

void line(){
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //GetConsoleScreenBufferInfo
    //COORD screen_buffer_size = {width, height};
    //SetConsoleScreenBufferSize(handle, &screen_buffer_size);
    
    SMALL_RECT rc = {1, 1, width + 1, height + 1}; // plus one for '\n'
    SetConsoleWindowInfo(handle, true, &rc);
    system("CLS");
    
    char ch[height][width + 1];
    
    vector<Fragment> p;
    p.clear();
    
    Rasterizer r(width, height, FILLING, 1);
    /*r.Rasterize(3, 4, 50, 20, p);
    r.Rasterize(50, 4, 3, 20, p);
    r.Rasterize(7, 1, 60, 1, p);
    r.Rasterize(30, 6, 30, 23, p);
    r.Rasterize(40, 20, 1, 1, p);
    r.Rasterize(40, 1, 1,20, p);
    
    r.Rasterize(1,1,2,20,p);
    r.Rasterize(3,1,8,20,p);
    r.Rasterize(10,1,27,20,p);*/
    Vertex v[] = {Vertex(2, 3, 0, 1.0f), Vertex(30, 20, 0, 1.0f), Vertex(50, 12, 0, 1.0f)};
    r.Rasterize(v[0], v[1], v[2], p);
    // r.Rasterize(v[0], v[1], p);
    // r.Rasterize(v[1], v[2], p);
    // r.Rasterize(v[0], v[2], p);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            ch[i][j] = GrayScale[0];
        }
        ch[i][width] = 0;
    }
    
    for (vector<Fragment>::iterator it = p.begin(); it != p.end(); ++it){
        int x = it->x, y = it->y;
        if (x >= 0 && x < width && y >= 0 && y < height){
            if (it->gray < EPS) ch[y][x] = GrayScale[0];
            else if (it->gray > 1 - EPS) ch[y][x] = GrayScale[MaxGrayScale - 1];
            else ch[y][x] = GrayScale[int(MaxGrayScale * it->gray)];
        }
    }

    string s = "";
    for (int i = 0; i < height; i++){
        /*
        for (int j = 0; j < width; j++){
            if (ch[i][j] == '*') {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            }
            else {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            }
            printf("%c", ch[i][j]);
        }
        */
        //printf("%s\n", ch[i]);
        s += ch[i];
        s += '\n';
    }
    printf("%s", s.c_str());
}