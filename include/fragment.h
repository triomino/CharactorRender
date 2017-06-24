#ifndef __FRAGMENT_H__
#define __FRAGMENT_H__

#include <string.h>

struct Fragment{
    int x;
    int y;
    float z; // depth
    float gray;
    Fragment(int _x = -1, int _y = -1) : x(_x), y(_y){}
    Fragment(int _x, int _y, float _z, float _gray) : x(_x), y(_y), z(_z), gray(_gray){}
};

const char GrayScale[] = " .:;=+*%#@";

const int MaxGrayScale = strlen(GrayScale);

#endif
