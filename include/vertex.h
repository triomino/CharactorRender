#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "fragment.h"

struct Vertex{
    float x;
    float y;
    float z;
    float gray;
    Vertex(){}
    Vertex(float _x, float _y, float _z = 0.0f, float _g = MaxGrayScale) : x(_x), y(_y), z(_z), gray(_g){}
};

#endif