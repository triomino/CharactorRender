#ifndef __FRAGMENT_H__
#define __FRAGMENT_H__

#include <string.h>
#include "my_math.h"

struct Fragment{
    int x;
    int y;
    float z; // depth
    float gray;
    //Fragment(int _x = -1, int _y = -1) : x(_x), y(_y){}
    Fragment(int _x = 0.0f, int _y = 0.0f, float _z = +INF, float _gray = 0.0f) : x(_x), y(_y), z(_z), gray(_gray){}
    
    void operator=(const Fragment &f){
        x = f.x, y = f.y, z = f.z, gray = f.gray;
    }
};

const char GrayScale[] = " .:;=+*%#@";

const int MaxGrayScale = strlen(GrayScale);

#endif
